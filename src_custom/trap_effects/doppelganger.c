#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateDOPPELGANGERZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DOPPELGANGER) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: when you take monster-effect damage → mirror to opp needs LP/effect-damage hook.
   * Ceiling: face-up continuous only; upgrade: after effect damage from opp
   * monster → Duel_ChangeLp(opp, -same).
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateDOPPELGANGEROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DOPPELGANGER, ActivateDOPPELGANGERZone);
}

