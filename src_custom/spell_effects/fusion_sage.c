#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

u8 CanActivateFusionSage(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0;
}

APPEND_TEXT void EffectFusionSage(void)
{
  const struct EffectScript *script = EffectScript_Find(FUSION_SAGE, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
