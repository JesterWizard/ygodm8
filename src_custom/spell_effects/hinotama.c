#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

LYN_REPLACE_CHECK(EffectHinotama);
APPEND_TEXT void EffectHinotama__Replacement(void)
{
  const struct EffectScript *script = EffectScript_Find(HINOTAMA, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
