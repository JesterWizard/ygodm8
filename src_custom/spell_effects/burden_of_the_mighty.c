#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void BURDEN_OF_THE_MIGHTY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(BURDEN_OF_THE_MIGHTY);

  /* ponytail: continuous -100 ATK × Level on each face-up opponent monster
   * needs a field-stat / continuous ATK overlay outside this file (no
   * in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays).
   * Ceiling: face-up continuous only; upgrade: stat overlay → if face-up
   * BURDEN_OF_THE_MIGHTY then each face-up opp monster ATK -= 100 * level. */
}

APPEND_TEXT void EffectBURDEN_OF_THE_MIGHTY(void)
{
  if (Duel_TryResolveSpellThroughTraps(BURDEN_OF_THE_MIGHTY, BURDEN_OF_THE_MIGHTY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
