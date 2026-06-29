#ifndef GUARD_ELEMENTAL_HERO_NECROSHADE_H
#define GUARD_ELEMENTAL_HERO_NECROSHADE_H

#include "global.h"

void ElementalHeroNecroshade_Reset(void);
u8 ElementalHeroNecroshade_CanNormalSummonWithoutTribute(u16 cardId);
u8 ElementalHeroNecroshade_CanNormalSummonWithoutTributeForHandSlot(u8 handSlot, u16 cardId);
u8 ElementalHeroNecroshade_TryConsumeOnNormalSummon(u16 cardId);

#endif // GUARD_ELEMENTAL_HERO_NECROSHADE_H
