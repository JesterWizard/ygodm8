#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target validation */
  (void)fixedRow;
  (void)fixedCol;
  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target resolution */
  (void)fixedRow;
  (void)fixedCol;
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  /* TODO: implement AI target selection */
  (void)outRow;
  (void)outCol;
  return FALSE;
}

unsigned char CanActivateHERALD_OF_ULTIMATENESS(void)
{
  if (gMonEffect.id != HERALD_OF_ULTIMATENESS)
    return FALSE;
  return TRUE; /* TODO: add additional activation conditions */
}

void ActivateHERALD_OF_ULTIMATENESSEffect(void)
{
  Duel_ShowEffectTextTyped(HERALD_OF_ULTIMATENESS, 2);

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
