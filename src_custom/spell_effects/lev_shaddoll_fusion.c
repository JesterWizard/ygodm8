#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void LEV_SHADDOLL_FUSION_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LEV_SHADDOLL_FUSION);

  /* ponytail: Extra Deck heavy — on-activate send 1 Fusion from Extra to GY, and
   * ignition (Tribute Fusion / SS Shaddoll Fusion different Attr ATK 0 / OPT /
   * no Extra SS that turn) all need a duel-time Extra Deck browser + SS path.
   * Trunk ExtraDeck_* APIs are deck-builder only. Ceiling: continuous face-up
   * text only; upgrade: Extra Deck pick/send + tribute+SS ignition with OPT flag. */
}

APPEND_TEXT void EffectLEV_SHADDOLL_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(LEV_SHADDOLL_FUSION, LEV_SHADDOLL_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
