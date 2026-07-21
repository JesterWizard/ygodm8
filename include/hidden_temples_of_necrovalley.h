#ifndef GUARD_HIDDEN_TEMPLES_OF_NECROVALLEY_H
#define GUARD_HIDDEN_TEMPLES_OF_NECROVALLEY_H

#include "global.h"

/* Wire into Duel_CardCannotBeSpecialSummoned after other summon gates. */
u8 HiddenTemplesOfNecrovalley_BlocksSpecialSummon(u16 cardId);

/* Wire after monster or backrow field changes. */
void HiddenTemplesOfNecrovalley_CheckAfterFieldChange(void);

#endif /* GUARD_HIDDEN_TEMPLES_OF_NECROVALLEY_H */
