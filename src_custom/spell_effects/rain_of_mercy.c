#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

APPEND_TEXT void EffectRainOfMercy(void)
{
  const struct EffectScript *script = EffectScript_Find(RAIN_OF_MERCY, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
