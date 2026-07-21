#ifndef GUARD_DESTINY_HERO_DOUBLE_DUDE_H
#define GUARD_DESTINY_HERO_DOUBLE_DUDE_H

#include "global.h"

void TryUnlockDestinyHeroDoubleDudeForSecondAttack(struct DuelCard *attacker);
void DestinyHeroDoubleDude_EnsureInit(void);
u8 ShouldActivateDestinyHeroDoubleDudeTurnEffect(void);
void ActivateDestinyHeroDoubleDudeTurnEffect(void);

#endif /* GUARD_DESTINY_HERO_DOUBLE_DUDE_H */
