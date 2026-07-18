#ifndef GUARD_CASINO_H
#define GUARD_CASINO_H

#include "gba/types.h"

#define CASINO_SPECIAL_BLACKJACK     36
#define CASINO_SPECIAL_CONCENTRATION 37

void Casino_BlackjackMain(void);
void Casino_ConcentrationMain(void);
/* After OverworldLoadGraphics — show win/lose text (+ card popup on ante win). */
void Casino_PresentOverworldResult(void);

/* Host-testable hand total: levels 1-11, 11 = Ace (soft then hard). */
u8 Casino_BlackjackHandTotal(const u8 *levels, u8 count);

#endif /* GUARD_CASINO_H */
