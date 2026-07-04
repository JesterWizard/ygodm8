#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "the_despair_uranus.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern u8 gDeferGraveyardDrawBattleResolve;

#define DESPAIR_URANUS_ATK_PER_SPELL_TRAP 300

static u8 IsSpellOrTrapCard(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  /* ponytail: GetTypeGroup → SetCardInfo clobbers gCardInfo.atk/def mid-pipeline. */
  return gCardData_NEW[cardId].type >= TYPE_SPELL;
}

static u8 IsActiveDespairUranus(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_DESPAIR_URANUS)
    return FALSE;

  if (IsCardFaceUp((struct DuelCard *)zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsDespairUranusInMonsterZone(u8 duelist)
{
  u8 monsterRow = duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[monsterRow][col]->id == THE_DESPAIR_URANUS)
      return TRUE;
  }

  return FALSE;
}

static u8 CountFaceUpSpellTrapsForDuelist(u8 duelist)
{
  u8 backrowRow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backrowRow][col];

    if (zone->id == CARD_NONE || !zone->isFaceUp)
      continue;

    if (IsSpellOrTrapCard(zone->id))
      count++;
  }

  return count;
}

static u8 IsCardEffectDestroyContext(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (Duel_IsSpellEffectResolving())
    return TRUE;

  if (Duel_IsMonsterEffectResolving())
    return TRUE;

  if (gTrapEffectData.trapCardId != 0)
    return TRUE;

  if (gActiveEffect.cardId != CARD_NONE)
    return TRUE;

  return FALSE;
}

void ApplyTheDespairUranusAtkBoost(struct DuelCard *zone)
{
  u8 duelist;
  u8 count;
  u32 atk;

  if (zone == NULL || zone->id != THE_DESPAIR_URANUS)
    return;

  /* ponytail: gCardInfo is already set for this zone by the caller. */
  if (gCardInfo.id != zone->id)
    return;

  if (!IsActiveDespairUranus(zone))
    return;

  duelist = GetDuelistForZone(zone);
  if (duelist == 0xFF || IsSkillDrainActiveOnField())
    return;

  count = CountFaceUpSpellTrapsForDuelist(duelist);
  if (count == 0)
    return;

  atk = (u32)gCardInfo.atk + (u32)count * DESPAIR_URANUS_ATK_PER_SPELL_TRAP;
  gCardInfo.atk = Duel_ClampStat(atk);
}

u8 IsTheDespairUranusProtectingZoneFromEffectDestroy(struct DuelCard *zone)
{
  u8 duelist;
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  if (!IsCardEffectDestroyContext())
    return FALSE;

  if (!Duel_FindFixedZone(zone, &fixedRow, &col))
    return FALSE;

  if (fixedRow != PLAYER_BACKROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  if (!IsSpellOrTrapCard(zone->id))
    return FALSE;

  duelist = GetDuelistForZone(zone);
  if (duelist == 0xFF)
    return FALSE;

  if (IsSkillDrainActiveOnField())
    return FALSE;

  return IsDespairUranusInMonsterZone(duelist);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheDespairUranus_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = THE_DESPAIR_URANUS;
  ApplyTheDespairUranusAtkBoost(&zone);

  zone.id = CARD_NONE;
  if (IsTheDespairUranusProtectingZoneFromEffectDestroy(&zone))
    while (1)
      ;
}
#endif
