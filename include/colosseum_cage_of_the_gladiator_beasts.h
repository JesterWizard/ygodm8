#ifndef GUARD_COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_H
#define GUARD_COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_H

#include "effect.h"

struct DuelCard;

#define COLOSSEUM_CAGE_ATK_DEF_PER_COUNTER 100

void ApplyColosseumCageStatForZone(struct DuelCard *zone);
void ColosseumCage_MarkSpecialSummonFromDeck(u8 controllerFixedDuelist);
u8 Cond_ColosseumCageOnDeckSpecialSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_ColosseumCageOnDeckSpecialSummon(struct EffectCtx *ctx);
u8 ColosseumCage_TryPreventDestroyByCardEffect(struct DuelCard *zone);

#endif /* GUARD_COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_H */
