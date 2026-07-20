#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateBACKFIREZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, BACKFIRE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: FIRE monster destroyed → 500 to opp needs destroy hook.
   * Ceiling: face-up continuous only; upgrade: OnDestroy FIRE face-up owned →
   * Duel_ChangeLp(opp, -500).
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateBACKFIREOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(BACKFIRE, ActivateBACKFIREZone);
}

/* ponytail: TryActivateBACKFIREOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
