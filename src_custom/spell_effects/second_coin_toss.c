#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void SECOND_COIN_TOSS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SECOND_COIN_TOSS);

  /* ponytail: redo coin toss (OPT) needs a shared coin-flip hook wrapping
   * RandRangeU8(0,1) / multi-coin callers (cup_of_ace, suit_of_sword_x, etc.).
   * Ceiling: continuous face-up only; upgrade: after coin resolve, if face-up
   * SECOND_COIN_TOSS on controller's field and effectUsedThisTurn clear, offer
   * redo (player confirm / AI heuristic), re-roll all flips, then mark OPT. */
}

APPEND_TEXT void EffectSECOND_COIN_TOSS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SECOND_COIN_TOSS, SECOND_COIN_TOSS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
