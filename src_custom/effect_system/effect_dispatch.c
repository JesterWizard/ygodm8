#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"

u8 EffectDispatch_TryActivate(u16 cardId, u8 kind)
{
  const struct EffectScript *script;

  if (cardId == CARD_NONE)
    return EFFECT_DISPATCH_LEGACY;

  script = EffectScript_Find(cardId, kind);
  if (script == NULL)
    return EFFECT_DISPATCH_LEGACY;

  if (EffectScript_Run(script))
    return EFFECT_DISPATCH_HANDLED;

  return EFFECT_DISPATCH_LEGACY;
}

u8 EffectDispatch_QueryShouldActivate(u16 cardId, u8 kind)
{
  const struct EffectScript *script;

  if (cardId == CARD_NONE)
    return EFFECT_SHOULD_NO;

  script = EffectScript_Find(cardId, kind);
  if (script == NULL)
    return EFFECT_SHOULD_LEGACY;

  if (script->canActivate != NULL && !script->canActivate())
    return EFFECT_SHOULD_NO;

  return EFFECT_SHOULD_YES;
}
