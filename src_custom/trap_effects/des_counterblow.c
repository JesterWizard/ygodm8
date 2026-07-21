#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateDES_COUNTERBLOWZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DES_COUNTERBLOW) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: destroy monster that inflicts direct battle damage needs battle LP hook.
   * Ceiling: face-up continuous only; upgrade: after direct battle damage →
   * Duel_DestroyZone(attacker).
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateDES_COUNTERBLOWOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DES_COUNTERBLOW, ActivateDES_COUNTERBLOWZone);
}

