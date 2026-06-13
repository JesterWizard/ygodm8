#ifndef GUARD_COFFIN_SELLER_H
#define GUARD_COFFIN_SELLER_H

#include "global.h"

extern u8 gPendingCoffinSellerDamageToPlayer;
extern u8 gPendingCoffinSellerDamageToOpponent;

u8 IsNonSelectableCoffinSellerZone(const struct DuelCard *zone);
void TryApplyCoffinSellerOnFieldLeave(struct DuelCard *zone);
void ResolveCoffinSellerBattleEffect(void);
void ClearCoffinSellerPending(void);
void EffectCoffinSeller(void);

#endif // GUARD_COFFIN_SELLER_H
