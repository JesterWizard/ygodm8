#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateALL_OUT_ATTACKSZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, ALL_OUT_ATTACKS) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: when monster(s) SS while face-up → change to ATK and must attack that turn.
   * Ceiling: face-up continuous only; upgrade: SS hook → isDefending=FALSE +
   * forced-attack flag.
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateALL_OUT_ATTACKSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ALL_OUT_ATTACKS, ActivateALL_OUT_ATTACKSZone);
}

/* ponytail: TryActivateALL_OUT_ATTACKSOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
