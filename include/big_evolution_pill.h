#ifndef GUARD_BIG_EVOLUTION_PILL_H
#define GUARD_BIG_EVOLUTION_PILL_H

#include "gba/types.h"

#define BIG_EVOLUTION_PILL_OPPONENT_END_PHASES 3

u8 CanActivateBIG_EVOLUTION_PILL(void);

/* Wire from turn_effect_hooks when a duelist's End Phase completes (pass ended fixed duelist). */
void BigEvolutionPill_OnOpponentEndPhase(u8 endedFixedDuelist);

u8 BigEvolutionPill_CanNormalSummonWithoutTribute(u16 cardId);
u8 BigEvolutionPill_TryConsumeOnNormalSummon(u16 cardId);

#endif /* GUARD_BIG_EVOLUTION_PILL_H */
