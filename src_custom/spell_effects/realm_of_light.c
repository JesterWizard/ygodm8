#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void REALM_OF_LIGHT_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(REALM_OF_LIGHT);

  /* ponytail: Shine Counters on mill / +100 ATK per counter on Lightsworn /
   * remove 2 counters instead of destroy need mill + destroy-gate + counter
   * storage outside this file (DuelCard has no shine-counter field; no in-file
   * Deck→GY or destroy dispatch). Ceiling: continuous face-up only; upgrade:
   * mill hook → if face-up REALM_OF_LIGHT controller's Deck→GY then ++counters;
   * Lightsworn ATK overlay += 100 * counters; Duel_DestroyZone on this card →
   * if counters >= 2 then counters -= 2 and skip destroy. */
}

APPEND_TEXT void EffectREALM_OF_LIGHT(void)
{
  if (Duel_TryResolveSpellThroughTraps(REALM_OF_LIGHT, REALM_OF_LIGHT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
