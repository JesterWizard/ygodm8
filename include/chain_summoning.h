#ifndef GUARD_CHAIN_SUMMONING_H
#define GUARD_CHAIN_SUMMONING_H

#include "gba/types.h"

#define CHAIN_SUMMONING_MIN_LINK 3
#define CHAIN_SUMMONING_EXTRA_NORMAL_SUMMONS 2

u8 CanActivateCHAIN_SUMMONING(void);
u8 ChainSummoning_CanActivateForChain(u8 linkCount, u8 sameNameOnChain);
void ChainSummoning_GrantExtraNormalSummons(void);
u8 ChainSummoning_ExtraSummonsRemaining(void);
u8 ChainSummoning_TryUnlockAfterNormalSummon(void);
void ChainSummoning_ResetTurnState(void);

#endif /* GUARD_CHAIN_SUMMONING_H */
