#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static void ActivateLIGHTSWORN_BARRIERZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHTSWORN_BARRIER) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: LS targeted for attack → mill top 2 → negate attack needs attack-
   * declaration hook. Ceiling: face-up continuous only; upgrade: on attack target
   * if Duel_CardNameContains(defender, Lightsworn) → mill 2 + NegateAttack. */
  (void)sLightswornName;
}

void TryActivateLIGHTSWORN_BARRIEROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHTSWORN_BARRIER, ActivateLIGHTSWORN_BARRIERZone);
}
