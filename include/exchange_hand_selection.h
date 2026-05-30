#ifndef GUARD_EXCHANGE_HAND_SELECTION_H
#define GUARD_EXCHANGE_HAND_SELECTION_H

#include "global.h"

s8 SelectExchangeHandCard(struct DuelCard **handRow);
s8 SelectHandCardMatchingType(struct DuelCard **handRow, u8 type);
void ShowExchangeOpponentHandResult(void);

#endif // GUARD_EXCHANGE_HAND_SELECTION_H
