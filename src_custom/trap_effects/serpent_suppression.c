#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sReptilianneName[] APPEND_RODATA = "Reptilianne";

static void ActivateSERPENT_SUPPRESSIONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, SERPENT_SUPPRESSION)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: opp 0-ATK Attack Position cannot be destroyed by battle with
   * Reptilianne needs battle-destroy gate. Ceiling: face-up continuous only. */
  (void)sReptilianneName;
}

void TryActivateSERPENT_SUPPRESSIONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SERPENT_SUPPRESSION,
                                         ActivateSERPENT_SUPPRESSIONZone);
}
