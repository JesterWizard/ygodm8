#ifndef GUARD_DESTINY_HERO_DOOM_LORD_H
#define GUARD_DESTINY_HERO_DOOM_LORD_H

#include "global.h"

#define DESTINY_HERO_DOOM_LORD_CANNOT_ATTACK_MARK 0x80

u8 DestinyHeroDoomLord_CanDeclareAttack(const struct DuelCard *zone);
void DestinyHeroDoomLord_ClearAttackLockAtEndPhase(void);

#endif /* GUARD_DESTINY_HERO_DOOM_LORD_H */
