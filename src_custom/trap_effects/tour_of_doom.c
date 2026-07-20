#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateTOUR_OF_DOOMZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, TOUR_OF_DOOM) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: opp Standby coin → Heads: opp cannot NS/Flip until EP; Tails: you cannot next turn.
   * Ceiling: face-up continuous only; upgrade: Standby turn_effect → RandRange
   * coin + summoningBlocked flags.
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateTOUR_OF_DOOMOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(TOUR_OF_DOOM, ActivateTOUR_OF_DOOMZone);
}

/* ponytail: TryActivateTOUR_OF_DOOMOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
