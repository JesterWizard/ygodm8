#ifndef GUARD_CHAIN_STRIKE_H
#define GUARD_CHAIN_STRIKE_H

#include "gba/types.h"

#define CHAIN_STRIKE_DAMAGE_PER_LINK 400
#define CHAIN_STRIKE_MIN_LINK 2

u8 CanActivateCHAIN_STRIKE(void);
u8 ChainStrike_GetEffectiveLinkCount(u8 reportedLink);
s32 ChainStrike_GetBurnDamage(u8 linkCount);
u8 ChainStrike_CanActivateForChain(u8 linkCount, u8 sameNameOnChain);

#endif /* GUARD_CHAIN_STRIKE_H */
