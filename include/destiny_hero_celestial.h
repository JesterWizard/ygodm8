#ifndef GUARD_DESTINY_HERO_CELESTIAL_H
#define GUARD_DESTINY_HERO_CELESTIAL_H

#include "global.h"

struct DuelCard;

void TryDestinyHeroCelestialOnAttackDeclared(struct DuelCard *attacker, struct DuelCard *defender);
u8 CanActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex);
void ActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex);

#endif // GUARD_DESTINY_HERO_CELESTIAL_H
