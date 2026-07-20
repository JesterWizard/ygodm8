#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

LYN_REPLACE_CHECK(EffectOokazi);
APPEND_TEXT void EffectOokazi__Replacement(void)
{
  const struct EffectScript *script = EffectScript_Find(OOKAZI, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
