#ifndef GUARD_FINAL_COUNTDOWN_H
#define GUARD_FINAL_COUNTDOWN_H

#include "global.h"

u8 CanActivateFinalCountdown(void);
u8 IsActivatedFinalCountdownZone(const struct DuelCard *zone);
void AgeFinalCountdownTurns(void);

#endif // GUARD_FINAL_COUNTDOWN_H
