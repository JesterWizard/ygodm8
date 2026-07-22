#ifndef GUARD_RESCUE_END_PHASE_H
#define GUARD_RESCUE_END_PHASE_H

#include "global.h"

#define RESCUE_SUMMON_END_PHASE_MARK 0x20

void RescueEndPhase_StampSummonedMonster(struct DuelCard *zone);
void TryApplyRescueEndPhaseDestroy(void);

#endif /* GUARD_RESCUE_END_PHASE_H */
