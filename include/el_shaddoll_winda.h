#ifndef GUARD_EL_SHADDOLL_WINDA_H
#define GUARD_EL_SHADDOLL_WINDA_H

#include "global.h"

u8 ElShaddollWinda_PreventsDestroy(const struct DuelCard *zone);
u8 ElShaddollWinda_IsSpecialSummonLockedFor(u8 turnDuelist);
void ElShaddollWinda_OnSpecialSummon(u8 turnDuelist);
void ElShaddollWinda_ClearTurnState(void);

#endif /* GUARD_EL_SHADDOLL_WINDA_H */
