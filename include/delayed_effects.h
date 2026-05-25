#ifndef GUARD_DELAYED_EFFECTS_H
#define GUARD_DELAYED_EFFECTS_H

#include "gba/types.h"

enum DelayedDuelEffectBit
{
  DELAYED_DUEL_EFFECT_CARD_OF_DEMISE = 1 << 0,
};

extern u8 gDelayedDuelEffects[2];

void ResetDelayedDuelEffects(void);
void QueueDelayedDuelEffect(u8 duelist, u8 effectBit);
u8 ConsumeDelayedDuelEffect(u8 duelist, u8 effectBit);
void ResolveDelayedDuelEffectsAtTurnEnd(u8 duelist);

#endif
