#ifndef GUARD_EXCHANGE_HAND_SELECTION_H
#define GUARD_EXCHANGE_HAND_SELECTION_H

#include "global.h"

typedef u8 (*HandCardPredicate)(u16 cardId);

s8 SelectExchangeHandCard(struct DuelCard **handRow);
s8 SelectHandCardMatchingType(struct DuelCard **handRow, u8 type);
s8 SelectHandCardMatchingPredicate(struct DuelCard **handRow, HandCardPredicate predicate);
s8 SelectHandCardMatchingPredicatePinnedFieldRow(struct DuelCard **handRow,
                                                 HandCardPredicate predicate,
                                                 u8 pinnedFieldRow);
void ShowExchangeOpponentHandResult(void);

#endif // GUARD_EXCHANGE_HAND_SELECTION_H
