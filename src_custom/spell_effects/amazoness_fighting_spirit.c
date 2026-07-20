#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* Activate = continuous place (CCTO script). Battle ATK: ON_DAMAGE_CALC. */
APPEND_TEXT void EffectAMAZONESS_FIGHTING_SPIRIT(void)
{
  const struct EffectScript *script =
      EffectScript_Find(AMAZONESS_FIGHTING_SPIRIT, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
