#ifndef GUARD_THE_DARK_DOOR_H
#define GUARD_THE_DARK_DOOR_H

#include "global.h"

u8 IsTheDarkDoorActiveOnField(void);
u8 IsActivatedTheDarkDoorZone(const struct DuelCard *zone);
u8 TheDarkDoor_CanAttackThisTurn(void);
void TheDarkDoor_MarkAttackUsed(void);
void TheDarkDoor_ResetTurnAttack(void);
void EffectTheDarkDoor(void);

#endif // GUARD_THE_DARK_DOOR_H
