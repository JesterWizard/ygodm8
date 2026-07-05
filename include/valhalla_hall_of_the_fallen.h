#ifndef GUARD_VALHALLA_HALL_OF_THE_FALLEN_H
#define GUARD_VALHALLA_HALL_OF_THE_FALLEN_H

#include "global.h"

u8 CanActivateValhallaHallOfTheFallenIgnition(struct DuelCard *zone);
void EffectValhallaHallOfTheFallen(void);
void TryUnlockHandForValhallaHallOfTheFallenIgnition(void);
void TryEnableValhallaHallOfTheFallenIgnitionAfterPlacement(void);

#endif // GUARD_VALHALLA_HALL_OF_THE_FALLEN_H
