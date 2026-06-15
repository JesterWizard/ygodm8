#ifndef GUARD_THE_A_FORCES_H
#define GUARD_THE_A_FORCES_H

#include "global.h"
#include "card.h"

u8 IsActivatedTheAForcesZone(const struct DuelCard *zone);
u8 IsTheAForcesActiveForDuelist(u8 duelist);
u8 ApplyTheAForcesAtkBonusToCardInfo(struct DuelCard *zone);
u8 ApplyTheAForcesStatsToCardInfo(struct StatMod *ptr);
void EffectTheAForces(void);

#endif // GUARD_THE_A_FORCES_H
