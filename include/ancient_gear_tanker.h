#ifndef GUARD_ANCIENT_GEAR_TANKER_H
#define GUARD_ANCIENT_GEAR_TANKER_H

#include "global.h"

#define ANCIENT_GEAR_PIERCE_MARK 0x08

void AncientGearTanker_MarkControllerPierce(u8 fixedDuelist);
u8 AncientGearMonsterHasPierceMark(const struct DuelCard *zone);

#endif /* GUARD_ANCIENT_GEAR_TANKER_H */
