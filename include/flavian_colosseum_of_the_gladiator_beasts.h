#ifndef GUARD_FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_H
#define GUARD_FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_H

#include "gba/types.h"

struct DuelCard;

void Flavian_MarkSpecialSummonFromDeck(u8 controllerFixedDuelist);
u8 Flavian_HasSpecialSummonedFromDeck(u8 controllerFixedDuelist);
void Flavian_OnAttackDeclare(void);
u8 Flavian_PreventsBattleDestroy(const struct DuelCard *zone);
void Flavian_ClearBattleDestroyProtection(const struct DuelCard *zone);
void TryApplyFlavianEndPhase(void);

#endif /* GUARD_FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_H */
