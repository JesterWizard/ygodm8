#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateAPPROPRIATEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, APPROPRIATE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: activate when opp draws outside Draw Phase; then each such draw → you draw 2.
   * Ceiling: face-up continuous only; upgrade: non-Draw-Phase draw hook →
   * Duel_DrawCards(controller, 2).
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateAPPROPRIATEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(APPROPRIATE, ActivateAPPROPRIATEZone);
}

