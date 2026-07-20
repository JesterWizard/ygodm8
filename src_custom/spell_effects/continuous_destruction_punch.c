#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* Activate = continuous place (CCTO). Battle: ApplyContinuousDestructionPunchBattleEffect. */
APPEND_TEXT void EffectCONTINUOUS_DESTRUCTION_PUNCH(void)
{
  const struct EffectScript *script =
      EffectScript_Find(CONTINUOUS_DESTRUCTION_PUNCH, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
