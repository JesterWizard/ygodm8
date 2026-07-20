#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateLIGHT_OF_DESTRUCTIONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHT_OF_DESTRUCTION) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: when opp effect mills their Deck → mill top 3 needs mill hook.
   * Ceiling: face-up continuous only; upgrade: after opp Deck→GY by effect →
   * send top 3 of that Deck to GY. */
}

void TryActivateLIGHT_OF_DESTRUCTIONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHT_OF_DESTRUCTION,
                                         ActivateLIGHT_OF_DESTRUCTIONZone);
}
