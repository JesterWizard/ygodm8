#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* ponytail: redo coin toss (OPT) needs a shared coin-flip hook wrapping
 * RandRangeU8(0,1) / multi-coin callers (cup_of_ace, suit_of_sword_x, etc.).
 * Ceiling: continuous face-up only; upgrade: after coin resolve, if face-up
 * SECOND_COIN_TOSS on controller's field and effectUsedThisTurn clear, offer
 * redo (player confirm / AI heuristic), re-roll all flips, then mark OPT. */

APPEND_TEXT void EffectSECOND_COIN_TOSS(void)
{
  const struct EffectScript *script = EffectScript_Find(SECOND_COIN_TOSS, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
