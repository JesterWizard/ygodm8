#ifndef GUARD_ELEMENTAL_HERO_CORE_H
#define GUARD_ELEMENTAL_HERO_CORE_H

#include "global.h"

#define ELEMENTAL_HERO_CORE_BATTLED_NONE 0xFF

extern u8 gElementalHeroCoreBattledRow;
extern u8 gElementalHeroCoreBattledCol;
extern u8 gElementalHeroCoreRevivePending;

void TryApplyElementalHeroCoreAtkDouble(void);
void ApplyElementalHeroCoreBattleEffect(void);
void ResolveElementalHeroCoreBattledEffect(void);
void ClearElementalHeroCoreBattledPending(void);
/* Mark only when Core is destroyed on the monster field (battle or effect). */
void MarkElementalHeroCoreDestroyedFromField(struct DuelCard *zone);
/* Clear arming if Core is sent from hand (discard). */
void ClearElementalHeroCoreReviveIfHandSend(struct DuelCard *zone);

unsigned char ShouldActivateElementalHeroCore(void);
void ActivateElementalHeroCore(void);
/* Call after FinishGraveyardDrawBattleResolve — shows popup_2 and GY revive. */
void ElementalHeroCore_TryResolveRevive(void);

#endif
