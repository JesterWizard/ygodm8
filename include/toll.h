#ifndef GUARD_TOLL_H
#define GUARD_TOLL_H

#include "global.h"

u8 IsActivatedTollZone(const struct DuelCard *zone);
u8 IsTollActiveOnField(void);
u8 TryPayTollAttackCost(void);
void EffectToll(void);

#endif // GUARD_TOLL_H
