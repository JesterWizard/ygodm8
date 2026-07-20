#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateTORNADO_WALLZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, TORNADO_WALL) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: activate only while Umi on field; no battle damage while Umi face-up;
   * destroy when Umi leaves. Ceiling: face-up continuous only; upgrade:
   * Umi field check on activate + battle-damage gate + Umi leave destroy.
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateTORNADO_WALLOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(TORNADO_WALL, ActivateTORNADO_WALLZone);
}

/* ponytail: TryActivateTORNADO_WALLOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
