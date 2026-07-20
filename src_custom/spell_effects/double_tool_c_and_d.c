#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";
static const char sPowerToolDragonName[] APPEND_RODATA = "Power Tool Dragon";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsDoubleToolEquipTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardNameContains(cardId, sPowerToolDragonName))
    return TRUE;

  if (!Duel_CardNameContains(cardId, sMorphtronicName))
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_MACHINE))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 4;
}

static u8 IsValidEquipTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsDoubleToolEquipTarget(zone->id);
}

static u8 HasEquipTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidEquipTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void DoubleToolOnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *monster = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ClearPickZone();
  if (monster == NULL || spellZone == NULL)
    return;

  if (!RegisterDynamicEquip(spellZone, monster, DOUBLE_TOOL_C_AND_D, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  /* ponytail: printed +1000 only on your turn + battle negate/redirect/destroy need
   * turn/battle hooks. Ceiling: equip link only (no ATK yet); upgrade: apply +2
   * stages on controller's turn via Duel_ResolveEquipStatBoost or overlay. */
  UpdateDuelGfxExceptField();
}

static void DoubleToolCancel(void)
{
  Duel_ClearPickZone();
}

static u8 DoubleToolValidate(u8 fixedRow, u8 fixedCol)
{
  return IsValidEquipTarget(fixedRow, fixedCol);
}

static u8 DoubleToolAiPick(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEquipTarget(row, col))
      continue;
    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateDOUBLE_TOOL_C_AND_D(void)
{
  return HasEquipTarget();
}

static void DOUBLE_TOOL_C_AND_D_ResolveBody(void)
{
  if (!CanActivateDOUBLE_TOOL_C_AND_D()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(DOUBLE_TOOL_C_AND_D);
  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(DoubleToolValidate, DoubleToolOnTarget, DoubleToolCancel,
                     DoubleToolAiPick);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectDOUBLE_TOOL_C_AND_D(void)
{
  if (Duel_TryResolveSpellThroughTraps(DOUBLE_TOOL_C_AND_D, DOUBLE_TOOL_C_AND_D_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
