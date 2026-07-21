#ifndef GUARD_SECOND_COIN_TOSS_H
#define GUARD_SECOND_COIN_TOSS_H

#include "gba/types.h"

u8 SecondCoinToss_CanRedo(u8 fixedDuelist);
void SecondCoinToss_MarkUsed(u8 fixedDuelist);
void SecondCoinToss_ClearOnTurnBoundary(void);
/* Returns 0 (tails) or 1 (heads). May re-roll once if Second Coin Toss OPT allows. */
u8 SecondCoinToss_Flip(u8 controllerFixed);

#endif /* GUARD_SECOND_COIN_TOSS_H */
