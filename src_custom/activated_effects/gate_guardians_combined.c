#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppCardTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppHasCard(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppCardTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;

    if (IsOppCardTarget(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroy(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppCardTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroy(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppCardTarget(OPPONENT_MONSTER_ROW, col)) {
      *outRow = OPPONENT_MONSTER_ROW;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppCardTarget(OPPONENT_BACKROW, col)) {
      *outRow = OPPONENT_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateGATE_GUARDIANS_COMBINED(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GATE_GUARDIANS_COMBINED)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GATE_GUARDIANS_COMBINED)
    return FALSE;

  /* ponytail: negate-on-target + leave-field SS FALSE.
   * Ceiling: OPT destroy 1 opp card (negate stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasCard();
}

void ActivateGATE_GUARDIANS_COMBINEDEffect(void)
{
  Duel_ShowEffectTextTyped(GATE_GUARDIANS_COMBINED, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppCardTarget, ResolveDestroy, CancelTargeting, AiPickDestroy);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
