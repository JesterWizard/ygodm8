#ifndef GUARD_AMAZONESS_CALL_H
#define GUARD_AMAZONESS_CALL_H

#include "global.h"

struct DuelCard;

u8 CanActivateAmazonessCallGy(u8 fixedDuelist, u8 gyIndex);
void ActivateAmazonessCallGy(u8 fixedDuelist, u8 gyIndex);

void ClearAmazonessCallMultiAttackState(void);
u8 AmazonessCall_CanAttackMonsterZone(struct DuelCard *zone);
void TryUnlockAmazonessCallForNextAttack(struct DuelCard *attacker,
                                         struct DuelCard *defender);

#endif /* GUARD_AMAZONESS_CALL_H */
