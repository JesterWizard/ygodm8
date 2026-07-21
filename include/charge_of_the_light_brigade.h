#ifndef GUARD_CHARGE_OF_THE_LIGHT_BRIGADE_H
#define GUARD_CHARGE_OF_THE_LIGHT_BRIGADE_H

#include "duel_helpers.h"

#define CHARGE_OF_THE_LIGHT_BRIGADE_MILL_COUNT 3
#define CHARGE_OF_THE_LIGHT_BRIGADE_MAX_LEVEL 4

u8 CanActivateCHARGE_OF_THE_LIGHT_BRIGADE(void);
enum DuelActionResult ChargeOfTheLightBrigade_MillDeckToGy(u8 turnDuelist, u8 count);

#endif /* GUARD_CHARGE_OF_THE_LIGHT_BRIGADE_H */
