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

}

APPEND_TEXT void EffectREALM_OF_LIGHT(void)
{
  if (Duel_TryResolveSpellThroughTraps(REALM_OF_LIGHT, REALM_OF_LIGHT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
