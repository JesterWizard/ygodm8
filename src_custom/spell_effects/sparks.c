#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* Body in effect_scripts (Phase 4b). LynJump kept if vanilla table is reached. */
LYN_REPLACE_CHECK(EffectSparks);
APPEND_TEXT void EffectSparks__Replacement(void)
{
  const struct EffectScript *script = EffectScript_Find(SPARKS, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
