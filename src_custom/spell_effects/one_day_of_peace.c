#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* Body lives in effect_scripts.c (Phase 4 C table). Symbol kept for generated decls. */
APPEND_TEXT void EffectONE_DAY_OF_PEACE(void)
{
  const struct EffectScript *script = EffectScript_Find(ONE_DAY_OF_PEACE, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
