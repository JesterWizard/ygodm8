#ifndef GUARD_EVIL_HERO_MALICIOUS_FIEND_H
#define GUARD_EVIL_HERO_MALICIOUS_FIEND_H

#include "global.h"

struct DuelCard *EvilHeroMaliciousFiend_GetForcedAttackTarget(u8 defenderDuelist);
u8 EvilHeroMaliciousFiend_CanAttackMonsterZone(struct DuelCard *zone);

#endif
