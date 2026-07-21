#ifndef GUARD_AMAZONESS_QUEEN_H
#define GUARD_AMAZONESS_QUEEN_H

#include "global.h"

/* Queen: Amazoness you control cannot be destroyed by battle.
 * Empress: other Amazoness you control cannot be destroyed by battle. */
u8 AmazonessQueen_PreventsBattleDestroy(const struct DuelCard *zone);

#endif /* GUARD_AMAZONESS_QUEEN_H */
