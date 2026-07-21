#ifndef GUARD_BERSERKER_SOUL_H
#define GUARD_BERSERKER_SOUL_H

#include "gba/types.h"

#define BERSERKER_SOUL_DIRECT_DAMAGE_MAX 1500

/* Wire from battle_damage_hooks on direct battle damage to defender. */
void BerserkerSoul_OnDirectDamage(s32 dmg);

u8 BerserkerSoul_CanActivateFromBattleFlag(void);

/* Wire from EffectEvent_OnTurnBoundary (effect_events.c). */
void BerserkerSoul_OnTurnBoundary(void);

#endif /* GUARD_BERSERKER_SOUL_H */
