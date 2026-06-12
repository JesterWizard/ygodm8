#ifndef GUARD_KAISER_GLIDER_H
#define GUARD_KAISER_GLIDER_H

#include "global.h"

#define DUEL_CURSOR_KAISER_GLIDER_TARGET 10

void ApplyKaiserGliderBattleProtection(void);
unsigned char ShouldActivateKaiserGlider(void);
void ActivateKaiserGlider(void);
void BeginKaiserGliderTargeting(void);
void TrySelectKaiserGliderTarget(void);
void CancelKaiserGliderTargeting(void);

#endif
