#ifndef GUARD_ORICHALCOS_SHUNOROS_H
#define GUARD_ORICHALCOS_SHUNOROS_H

#include "global.h"

u8 OrichalcosShunoros_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 OrichalcosShunoros_PreventsBattleDestroy(const struct DuelCard *zone);
void TryOrichalcosShunorosSsAfterNormalMonsterBd(u8 fixedDuelist, u16 cardId);

u8 CanSpecialSummonOrichalcosShunorosFromHand(u8 handZone);
u8 TrySpecialSummonOrichalcosShunorosFromHand(u8 handZone);

#endif /* GUARD_ORICHALCOS_SHUNOROS_H */
