#ifndef GUARD_PARALLEL_WORLD_FUSION_H
#define GUARD_PARALLEL_WORLD_FUSION_H

#include "gba/types.h"

void ParallelWorldFusion_MarkSpecialSummonLock(void);
void ParallelWorldFusion_ClearOnTurnBoundary(void);
u8 ParallelWorldFusion_BlocksSpecialSummon(u16 cardId);

#endif /* GUARD_PARALLEL_WORLD_FUSION_H */
