#ifndef GUARD_GLADIATOR_BEAST_BATTLED_H
#define GUARD_GLADIATOR_BEAST_BATTLED_H

#include "global.h"

#define GLADIATOR_BEAST_BATTLED_MARK 0x20

struct DuelCard;

u8 GladiatorBeast_ZoneBattledThisBattlePhase(const struct DuelCard *zone);
void ApplyGladiatorBeastBattledMarks(void);
void ClearGladiatorBeastBattledMarks(void);

#endif /* GUARD_GLADIATOR_BEAST_BATTLED_H */
