#ifndef GUARD_EN_WAVE_H
#define GUARD_EN_WAVE_H

#include "effect_events.h"

/* Subscribe these only after the parent has identified the semantic event. */
void EN_WAVE_OnFusionMaterialLeave(const struct EffectEvent *ev);
void EN_WAVE_OnShuffleIntoDeck(const struct EffectEvent *ev);

#endif /* GUARD_EN_WAVE_H */
