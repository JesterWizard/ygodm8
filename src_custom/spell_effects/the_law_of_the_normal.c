#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "spell_effects.h"

#define LAW_OF_THE_NORMAL_MAX_LEVEL 2
#define LAW_OF_THE_NORMAL_REQUIRED_COUNT 5

void UpdateDuelGfxExceptField(void);

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsLevel2OrLowerNormalMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  return gCardInfo.level > 0 && gCardInfo.level <= LAW_OF_THE_NORMAL_MAX_LEVEL;
}

static u8 CountFaceUpLv2NormalsOnActiveField(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!MonsterIsFaceUp(zone))
      continue;
    if (!IsLevel2OrLowerNormalMonster(zone->id))
      continue;

    count++;
  }

  return count;
}

static u8 ShouldDestroyByLawOfTheNormal(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  /* Keep Level 2 or lower Normal Monsters. */
  return !IsLevel2OrLowerNormalMonster(zone->id);
}

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void DestroyAllSpellsAndTrapsOnField(void)
{
  u8 pass;
  u8 col;
  u8 destroyed = FALSE;

  for (pass = 0; pass < 2; pass++) {
    u8 row = (pass == 0) ? OPPONENT_BACKROW : PLAYER_BACKROW;
    u8 graveyardDuelist = GraveyardDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || !IsSpellOrTrapCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

u8 CanActivateTHE_LAW_OF_THE_NORMAL(void)
{
  return CountFaceUpLv2NormalsOnActiveField() >= LAW_OF_THE_NORMAL_REQUIRED_COUNT;
}

static void THE_LAW_OF_THE_NORMAL_ResolveBody(void)
{
  Duel_ShowEffectText(THE_LAW_OF_THE_NORMAL);

  if (IsDuelOver() == TRUE || !CanActivateTHE_LAW_OF_THE_NORMAL())
    return;

  if (Duel_DestroyAllHandCards(ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllHandCards(INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW,
                                      ShouldDestroyByLawOfTheNormal, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW,
                                      ShouldDestroyByLawOfTheNormal, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  DestroyAllSpellsAndTrapsOnField();
  if (IsDuelOver() == TRUE)
    return;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectTHE_LAW_OF_THE_NORMAL(void)
{
  if (!CanActivateTHE_LAW_OF_THE_NORMAL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_LAW_OF_THE_NORMAL,
                                       THE_LAW_OF_THE_NORMAL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_LAW_OF_THE_NORMAL_SelfCheck(void)
{
  if (!IsLevel2OrLowerNormalMonster(MUSHROOM_MAN))
    while (1)
      ;
  if (IsLevel2OrLowerNormalMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsLevel2OrLowerNormalMonster(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
