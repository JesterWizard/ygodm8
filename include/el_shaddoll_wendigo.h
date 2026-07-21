#ifndef GUARD_EL_SHADDOLL_WENDIGO_H
#define GUARD_EL_SHADDOLL_WENDIGO_H

#include "global.h"

#define EL_SHADDOLL_WENDIGO_BATTLE_PROTECT_MARK 0x40

u8 ElShaddollWendigo_PreventsBattleDestroy(const struct DuelCard *zone);
void ElShaddollWendigo_ClearTurnMarks(void);

#endif /* GUARD_EL_SHADDOLL_WENDIGO_H */
