#ifndef GUARD_HERO_FLASH_H
#define GUARD_HERO_FLASH_H

#include "global.h"

/* Wire into player and AI direct-attack legality checks. */
u8 HeroFlash_CanMonsterAttackDirectly(const struct DuelCard *zone);

#endif /* GUARD_HERO_FLASH_H */
