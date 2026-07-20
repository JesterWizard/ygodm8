#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

APPEND_TEXT void EffectThunderCrash(void)
{
  const struct EffectScript *script = EffectScript_Find(THUNDER_CRASH, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
