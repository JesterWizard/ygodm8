#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static void ActivateMORPHTRONIC_BINDZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, MORPHTRONIC_BIND) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: while face-up Morphtronic controlled, opp Lv≥4 cannot attack or
   * change battle position needs attack/position gates. Ceiling: face-up
   * continuous only. */
  (void)sMorphtronicName;
}

void TryActivateMORPHTRONIC_BINDOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(MORPHTRONIC_BIND, ActivateMORPHTRONIC_BINDZone);
}
