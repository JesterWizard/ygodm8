#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define WINGBEAT_MIN_LEVEL 5

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsLevel5OrHigherDragon(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_DRAGON
      && gCardData_NEW[cardId].level >= WINGBEAT_MIN_LEVEL;
}

static u8 IsValidWingbeatTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsLevel5OrHigherDragon(zone->id);
}

static u8 HasWingbeatTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidWingbeatTarget(ActiveMonsterFixedRow(), col))
      return TRUE;
  }

  return FALSE;
}

static u8 HasHandRoomForReturn(void)
{
  return NumEmptyZonesInRow(gTurnHands[ACTIVE_DUELIST]) > 0;
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

static void DestroyWingbeatSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == A_WINGBEAT_OF_GIANT_DRAGON)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveWingbeatTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidWingbeatTarget(fixedRow, fixedCol))
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  DestroyAllSpellsAndTrapsOnField();
  if (IsDuelOver() == TRUE)
    return;

  DestroyWingbeatSpellZone();
}

static void CancelWingbeatTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  /* Activation already committed past traps — send the spell to GY. */
  DestroyWingbeatSpellZone();
}

static u8 AiPickWingbeatTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidWingbeatTarget(monsterRow, col))
      continue;

    *outRow = monsterRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateA_WINGBEAT_OF_GIANT_DRAGON(void)
{
  return HasWingbeatTarget() && HasHandRoomForReturn();
}

static void A_WINGBEAT_OF_GIANT_DRAGON_ResolveBody(void)
{
  Duel_ShowEffectText(A_WINGBEAT_OF_GIANT_DRAGON);

  if (IsDuelOver() == TRUE || !CanActivateA_WINGBEAT_OF_GIANT_DRAGON())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidWingbeatTarget, ResolveWingbeatTarget, CancelWingbeatTargeting,
                     AiPickWingbeatTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectA_WINGBEAT_OF_GIANT_DRAGON(void)
{
  if (!CanActivateA_WINGBEAT_OF_GIANT_DRAGON()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(A_WINGBEAT_OF_GIANT_DRAGON,
                                       A_WINGBEAT_OF_GIANT_DRAGON_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void A_WINGBEAT_OF_GIANT_DRAGON_SelfCheck(void)
{
  if (!IsLevel5OrHigherDragon(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsLevel5OrHigherDragon(BABY_DRAGON))
    while (1)
      ;
  if (!IsSpellOrTrapCard(MYSTICAL_SPACE_TYPHOON))
    while (1)
      ;
}
#endif
