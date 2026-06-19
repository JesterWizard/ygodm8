#ifndef GUARD_GHOST_KNIGHT_OF_JACKAL_H
#define GUARD_GHOST_KNIGHT_OF_JACKAL_H

#include "global.h"

#define GHOST_KNIGHT_OF_JACKAL_PENDING_NONE 0xFF

extern u8 gGhostKnightOfJackalPendingController;
extern u8 gGhostKnightOfJackalPendingGraveyardDuelist;

void ApplyGhostKnightOfJackalBattleEffect(void);
void ResolveGhostKnightOfJackalBattleEffect(void);
void ClearGhostKnightOfJackalPending(void);

#endif
