#ifndef GUARD_SOUL_EXCHANGE_H
#define GUARD_SOUL_EXCHANGE_H

#include "global.h"

extern u8 gSoulExchangeActive;
extern u8 gSoulExchangeTributeCredit;

u8 IsSoulExchangeActive(void);
void ClearSoulExchangeTributeCredit(void);
void ActivateSoulExchangeForTurn(void);
void ClearSoulExchange(void);
void GrantSoulExchangeTributeCredit(void);
u8 CanActivateSoulExchange(void);
void ApplyMonsterTributeFromFixedRow(struct DuelCard *zone, u8 fixedMonsterRow);
void PerformSoulExchangeOpponentTribute(void);

#endif // GUARD_SOUL_EXCHANGE_H
