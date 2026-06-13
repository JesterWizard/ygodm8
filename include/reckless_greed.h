#ifndef GUARD_RECKLESS_GREED_H
#define GUARD_RECKLESS_GREED_H

#include "global.h"

#define RECKLESS_GREED_SKIP_DRAW_NONE 0xFF

extern u8 gRecklessGreedSkipDrawDuelist;
extern u8 gRecklessGreedSkipDrawRemaining;

void ResetRecklessGreedSkipDraw(void);
u8 ShouldSkipDrawPhaseForRecklessGreed(u8 turn);
void ConsumeRecklessGreedSkipDraw(u8 turn);
void TryActivateRecklessGreedOnOpponentTurnStart(void);

#endif // GUARD_RECKLESS_GREED_H
