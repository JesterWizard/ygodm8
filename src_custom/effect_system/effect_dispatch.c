#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect.h"
#include "effect_system.h"

u8 EffectDispatch_TryActivate(u16 cardId, u8 kind)
{
  if (cardId == CARD_NONE)
    return EFFECT_DISPATCH_LEGACY;

  /* Uniform Effect CCTO path (script-backed or hand-authored). */
  return Effect_TryActivate(cardId, kind);
}

u8 EffectDispatch_QueryShouldActivate(u16 cardId, u8 kind)
{
  if (cardId == CARD_NONE)
    return EFFECT_SHOULD_NO;

  return Effect_QueryShouldActivate(cardId, kind);
}
