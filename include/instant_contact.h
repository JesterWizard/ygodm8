#ifndef GUARD_INSTANT_CONTACT_H
#define GUARD_INSTANT_CONTACT_H

#include "gba/types.h"

struct DuelCard;

void InstantContact_StampRestrictedSummon(struct DuelCard *zone);
/* Wire clear from every monster-zone leave path. */
void InstantContact_ClearRestrictedSummon(const struct DuelCard *zone);
/* Wire into monster-effect and End Phase Extra Deck-return checks. */
u8 InstantContact_NegatesMonsterEffects(const struct DuelCard *zone);
u8 InstantContact_ShouldReturnToExtraDeckAtEndPhase(const struct DuelCard *zone);

#endif /* GUARD_INSTANT_CONTACT_H */
