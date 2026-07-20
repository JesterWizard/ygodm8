#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateSOUL_LEVYZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, SOUL_LEVY) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: only control 1 + each opp SS → mill top 3 opp Deck need unique-
   * continuous + summon hook. Ceiling: face-up continuous only; upgrade:
   * after opp Special Summon → send top 3 of opp Deck to GY. */
}

void TryActivateSOUL_LEVYOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SOUL_LEVY, ActivateSOUL_LEVYZone);
}
