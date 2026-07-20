#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static void ActivateMORPHTRONIC_MONITRONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, MORPHTRONIC_MONITRON)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: when Morphtronic Summoned → optional to Defense needs summon hook.
   * Ceiling: face-up continuous only. */
  (void)sMorphtronicName;
}

void TryActivateMORPHTRONIC_MONITRONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(MORPHTRONIC_MONITRON,
                                         ActivateMORPHTRONIC_MONITRONZone);
}
