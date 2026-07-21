#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define MASK_OF_DISPEL_STANDBY_DAMAGE 500

static u8 IsSameFixedZone(u8 rowA, u8 colA, u8 rowB, u8 colB)
{
  return rowA == rowB && colA == colB;
}

static u8 IsValidMaskOfDispelTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  /* Exclude self (Mask of Dispel origin). */
  if (IsSameFixedZone(fixedRow, fixedCol, gSpellEffectData.row1, gSpellEffectData.col1))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
    return FALSE;

  return zone->isFaceUp == TRUE;
}

static u8 HasMaskOfDispelTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidMaskOfDispelTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateMASK_OF_DISPEL(void)
{
  u8 savedRow1 = gSpellEffectData.row1;
  u8 savedCol1 = gSpellEffectData.col1;
  u8 ok;

  /* Exclude self: spell-effect origin after ActivateSpellEffect, else cursor. */
  if (gSpellEffectData.id == MASK_OF_DISPEL) {
    /* row1/col1 already origin */
  } else {
    gSpellEffectData.row1 = gDuelCursor.currentY;
    gSpellEffectData.col1 = gDuelCursor.currentX;
  }

  ok = HasMaskOfDispelTarget();
  gSpellEffectData.row1 = savedRow1;
  gSpellEffectData.col1 = savedCol1;
  return ok;
}

static void StashMaskOfDispelTarget(struct DuelCard *spellZone, u8 fixedRow, u8 fixedCol)
{
  /* Encode target as (row << 4) | col, plus 1 so 0 means "no target". */
  spellZone->unk4 = (u8)((((fixedRow & 0xF) << 4) | (fixedCol & 0xF)) + 1);
}

static u8 IsActivatedMaskOfDispelZone(const struct DuelCard *spellZone)
{
  return spellZone != NULL && spellZone->id == MASK_OF_DISPEL && spellZone->isFaceUp == TRUE
      && spellZone->isLocked == TRUE && spellZone->unk4 > 0;
}

static struct DuelCard *MaskOfDispelGetTarget(const struct DuelCard *spellZone)
{
  u8 target = spellZone->unk4 - 1;
  u8 fixedRow = target >> 4;
  u8 fixedCol = target & 0xF;
  struct DuelCard *targetZone;

  if (!IsActivatedMaskOfDispelZone(spellZone))
    return NULL;

  if ((fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
      || fixedCol >= MAX_ZONES_IN_ROW)
    return NULL;

  targetZone = gFixedZones[fixedRow][fixedCol];
  if (targetZone == NULL || targetZone->id == CARD_NONE)
    return NULL;

  return GetTypeGroup(targetZone->id) == TYPE_GROUP_SPELL ? targetZone : NULL;
}

void MaskOfDispel_OnTargetLeave(struct DuelCard *zone)
{
  u8 row;
  u8 col;
  struct DuelCard *spellZone;

  if (gHideEffectText || zone == NULL || GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gFixedZones[row][col];
      if (MaskOfDispelGetTarget(spellZone) != zone)
        continue;

      Duel_DestroyZone(spellZone, row == PLAYER_BACKROW ? DUEL_PLAYER : DUEL_OPPONENT, TRUE);
    }
  }
}

void TryApplyMaskOfDispelStandbyDamage(void)
{
  u8 col;
  struct DuelCard *spellZone;
  struct DuelCard *target;
  u8 targetRow;

  if (IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];
    target = MaskOfDispelGetTarget(spellZone);
    if (target == NULL)
      continue;

    targetRow = (spellZone->unk4 - 1) >> 4;
    Duel_ShowEffectTextTyped(MASK_OF_DISPEL, 9);
    if (Duel_ChangeLp(targetRow == PLAYER_BACKROW ? DUEL_PLAYER : DUEL_OPPONENT,
                      -MASK_OF_DISPEL_STANDBY_DAMAGE, TRUE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

static void FinishMaskOfDispel(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone == NULL || spellZone->id != MASK_OF_DISPEL)
    return;

  if (!IsValidMaskOfDispelTarget(fixedRow, fixedCol))
    return;

  StashMaskOfDispelTarget(spellZone, fixedRow, fixedCol);
  Duel_ActivateContinuousZone(spellZone);
}

static void CancelMaskOfDispelTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == MASK_OF_DISPEL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 AiPickMaskOfDispelTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidMaskOfDispelTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveMaskOfDispelTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidMaskOfDispelTarget(fixedRow, fixedCol))
    return;

  FinishMaskOfDispel(fixedRow, fixedCol);
}

static void MASK_OF_DISPEL_ResolveBody(void)
{
  Duel_ShowEffectText(MASK_OF_DISPEL);

  if (IsDuelOver() == TRUE || !CanActivateMASK_OF_DISPEL())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMaskOfDispelTarget, ResolveMaskOfDispelTarget,
                     CancelMaskOfDispelTargeting, AiPickMaskOfDispelTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMASK_OF_DISPEL(void)
{
  if (!CanActivateMASK_OF_DISPEL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MASK_OF_DISPEL, MASK_OF_DISPEL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MASK_OF_DISPEL_SelfCheck(void)
{
  if (MASK_OF_DISPEL_STANDBY_DAMAGE != 500)
    while (1)
      ;
}
#endif
