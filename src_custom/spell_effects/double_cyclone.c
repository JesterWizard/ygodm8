#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* Own S/T pick stashed in gSpellEffectData.row2/col2 (spell stays in row1/col1). */

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 InactiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsValidOwnSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 IsValidOpponentSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 HasOwnSpellTrap(void)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOwnSpellTrapTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 HasOpponentSpellTrap(void)
{
  u8 col;
  u8 row = InactiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOpponentSpellTrapTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void DestroyDoubleCycloneSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == DOUBLE_CYCLONE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void DestroySpellTrapAt(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE || !IsSpellOrTrapCard(zone->id))
    return;

  Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE);
}

static void FinishDoubleCyclone(u8 oppRow, u8 oppCol)
{
  DestroySpellTrapAt(gSpellEffectData.row2, gSpellEffectData.col2);
  if (IsDuelOver() == TRUE)
    return;

  DestroySpellTrapAt(oppRow, oppCol);
  if (IsDuelOver() == TRUE)
    return;

  NotifyDynamicEquipFieldChanged();

  /* If Double Cyclone was not one of the two targets, still send it to GY. */
  DestroyDoubleCycloneSpellZone();
}

static void CancelDoubleCycloneTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  /* Activation already committed past traps — send the spell to GY. */
  DestroyDoubleCycloneSpellZone();
}

static u8 AiPickOpponentSpellTrap(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = InactiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidOpponentSpellTrapTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveOpponentSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidOpponentSpellTrapTarget(fixedRow, fixedCol))
    return;

  FinishDoubleCyclone(fixedRow, fixedCol);
}

static void BeginOpponentSpellTrapPick(void)
{
  Duel_SetupPickZone(IsValidOpponentSpellTrapTarget, ResolveOpponentSpellTrapTarget,
                     CancelDoubleCycloneTargeting, AiPickOpponentSpellTrap);
  Duel_EnterPickZoneTargeting();
}

static u8 AiPickOwnSpellTrap(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidOwnSpellTrapTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveOwnSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidOwnSpellTrapTarget(fixedRow, fixedCol))
    return;

  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;

  if (!HasOpponentSpellTrap()) {
    DestroyDoubleCycloneSpellZone();
    return;
  }

  /* Re-enter PickZone for opponent backrow (multi-pick; see duel_helpers). */
  BeginOpponentSpellTrapPick();
}

static void ResolveDoubleCycloneForAi(void)
{
  u8 ownRow;
  u8 ownCol;
  u8 oppRow;
  u8 oppCol;

  if (!AiPickOwnSpellTrap(&ownRow, &ownCol) || !AiPickOpponentSpellTrap(&oppRow, &oppCol)) {
    DestroyDoubleCycloneSpellZone();
    return;
  }

  gSpellEffectData.row2 = ownRow;
  gSpellEffectData.col2 = ownCol;
  FinishDoubleCyclone(oppRow, oppCol);
}

u8 CanActivateDOUBLE_CYCLONE(void)
{
  return HasOwnSpellTrap() && HasOpponentSpellTrap();
}

static void DOUBLE_CYCLONE_ResolveBody(void)
{
  Duel_ShowEffectText(DOUBLE_CYCLONE);

  if (IsDuelOver() == TRUE || !CanActivateDOUBLE_CYCLONE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolveDoubleCycloneForAi();
    return;
  }

  Duel_SetupPickZone(IsValidOwnSpellTrapTarget, ResolveOwnSpellTrapTarget,
                     CancelDoubleCycloneTargeting, AiPickOwnSpellTrap);
  Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectDOUBLE_CYCLONE(void)
{
  if (!CanActivateDOUBLE_CYCLONE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DOUBLE_CYCLONE, DOUBLE_CYCLONE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DOUBLE_CYCLONE_SelfCheck(void)
{
  if (!IsSpellOrTrapCard(MYSTICAL_SPACE_TYPHOON))
    while (1)
      ;
  if (!IsSpellOrTrapCard(DOUBLE_CYCLONE))
    while (1)
      ;
  if (IsSpellOrTrapCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
