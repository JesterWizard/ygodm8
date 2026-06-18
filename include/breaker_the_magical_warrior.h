#ifndef GUARD_BREAKER_THE_MAGICAL_WARRIOR_H
#define GUARD_BREAKER_THE_MAGICAL_WARRIOR_H

#include "global.h"

#define DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET 16

u8 BreakerTheMagicalWarrior_ZoneHasSpellCounter(const struct DuelCard *zone);
void BreakerTheMagicalWarrior_ClearZoneSpellCounter(struct DuelCard *zone);
void TryBreakerTheMagicalWarriorOnMonsterPlacement(struct DuelCard *zone);
unsigned char CanActivateBreakerTheMagicalWarrior(void);
void ActivateBreakerTheMagicalWarriorEffect(void);
void TrySelectBreakerTheMagicalWarriorTarget(void);
void CancelBreakerTheMagicalWarriorTargeting(void);

#endif // GUARD_BREAKER_THE_MAGICAL_WARRIOR_H
