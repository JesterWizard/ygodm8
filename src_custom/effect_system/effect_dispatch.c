#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_system.h"

/*
 * Phase 0: empty conversion table. Every card falls through to legacy handlers.
 * Phase 1+ will look up C effect tables here before returning HANDLED.
 */

u8 EffectDispatch_TryActivate(u16 cardId, u8 kind)
{
  (void)kind;

  if (cardId == CARD_NONE)
    return EFFECT_DISPATCH_LEGACY;

  /* ponytail: Phase 0 has no converted cards. Upgrade: table lookup → run script. */
  return EFFECT_DISPATCH_LEGACY;
}

u8 EffectDispatch_QueryShouldActivate(u16 cardId, u8 kind)
{
  (void)kind;

  if (cardId == CARD_NONE)
    return EFFECT_SHOULD_NO;

  /* ponytail: Phase 0 has no converted cards. Upgrade: table shouldActivate bit. */
  return EFFECT_SHOULD_LEGACY;
}
