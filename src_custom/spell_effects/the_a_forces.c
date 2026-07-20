#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void THE_A_FORCES_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(THE_A_FORCES);

  /* ponytail: continuous +200 ATK per Warrior/Spellcaster you control on your
   * Warriors needs a field-stat / continuous ATK overlay outside this file (no
   * in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays).
   * Ceiling: face-up continuous only; upgrade: stat overlay → if face-up
   * THE_A_FORCES then each face-up Warrior you control ATK += 200 *
   * (Warrior + Spellcaster count you control). */
}

APPEND_TEXT void EffectTHE_A_FORCES(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_A_FORCES, THE_A_FORCES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
