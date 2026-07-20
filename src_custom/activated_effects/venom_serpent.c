#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* Venom Counter stand-in on unk4. */
  zone->unk4++;
  if (self != NULL)
    MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OpponentMonsterRow();
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OpponentMonsterRow(), col))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateVENOM_SERPENT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != VENOM_SERPENT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VENOM_SERPENT)
    return FALSE;

  return CanUseMonsterEffect(zone) && FieldHasTarget();
}

void ActivateVENOM_SERPENTEffect(void)
{
  Duel_ShowEffectTextTyped(VENOM_SERPENT, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
