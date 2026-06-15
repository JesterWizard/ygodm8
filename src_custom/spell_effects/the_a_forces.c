#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "imperial_order.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "the_a_forces.h"

void UpdateDuelGfxExceptField(void);

#define THE_A_FORCES_ATK_PER_MONSTER 200

extern struct DuelCard *gSetFinalStatZone;

static u8 MonsterRowForDuelist(u8 duelist)
{
  return duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsFaceUpMonsterOnField(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsWarriorMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_WARRIOR;
}

static u8 IsWarriorOrSpellcasterMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_WARRIOR || gCardInfo.type == TYPE_SPELLCASTER;
}

static u8 CountWarriorOrSpellcasterMonsters(u8 duelist)
{
  u8 i;
  u8 count = 0;
  u8 monsterRow = MonsterRowForDuelist(duelist);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];

    if (!IsFaceUpMonsterOnField(zone))
      continue;
    if (!IsWarriorOrSpellcasterMonster(zone->id))
      continue;
    count++;
  }

  return count;
}

u8 IsActivatedTheAForcesZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == THE_A_FORCES && zone->isFaceUp == TRUE && zone->isLocked == TRUE;
}

u8 IsTheAForcesActiveForDuelist(u8 duelist)
{
  u8 backrowRow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 i;

  if (IsImperialOrderNegatingSpell(THE_A_FORCES))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsActivatedTheAForcesZone(gFixedZones[backrowRow][i]))
      return TRUE;
  }

  return FALSE;
}

static u16 TheAForcesAtkBonusForDuelist(u8 duelist)
{
  u32 bonus;

  if (!IsTheAForcesActiveForDuelist(duelist))
    return 0;

  bonus = (u32)CountWarriorOrSpellcasterMonsters(duelist) * THE_A_FORCES_ATK_PER_MONSTER;
  if (bonus > 0xFFFE)
    return 0xFFFE;
  return (u16)bonus;
}

u8 ApplyTheAForcesAtkBonusToCardInfo(struct DuelCard *zone)
{
  u8 duelist;
  u16 bonus;

  if (zone == NULL || zone->id == CARD_NONE || !IsWarriorMonster(zone->id))
    return FALSE;

  duelist = GetDuelistForZone(zone);
  if (duelist == 0xFF)
    return FALSE;

  bonus = TheAForcesAtkBonusForDuelist(duelist);
  if (bonus == 0)
    return FALSE;

  gCardInfo.atk += bonus;
  if (gCardInfo.atk > 0xFFFE)
    gCardInfo.atk = 0xFFFE;
  return TRUE;
}

u8 ApplyTheAForcesStatsToCardInfo(struct StatMod *ptr)
{
  u8 row;
  u8 col;

  if (ptr == NULL || !IsWarriorMonster(ptr->card))
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == ptr->card)
    return ApplyTheAForcesAtkBonusToCardInfo(gSetFinalStatZone);

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != ptr->card)
        continue;
      if (GetFinalStage(zone) != ptr->stage)
        continue;
      if (ApplyTheAForcesAtkBonusToCardInfo(zone))
        return TRUE;
    }
  }

  return FALSE;
}

APPEND_TEXT void EffectTheAForces(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  Duel_ShowEffectText(THE_A_FORCES);
}

#if !defined(__GNUC__)
#error The A. Forces self-check requires GCC
#elif __GNUC__
void TheAForces_SelfCheck(void)
{
  struct DuelCard zone;
  struct StatMod statMod;

  zone.id = CARD_NONE;
  ApplyTheAForcesAtkBonusToCardInfo(&zone);

  statMod.card = THE_A_FORCES;
  statMod.field = 0;
  statMod.stage = 0;
  ApplyTheAForcesStatsToCardInfo(&statMod);
}
#endif
