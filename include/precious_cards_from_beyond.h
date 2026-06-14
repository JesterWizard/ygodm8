#ifndef GUARD_PRECIOUS_CARDS_FROM_BEYOND_H
#define GUARD_PRECIOUS_CARDS_FROM_BEYOND_H

#include "global.h"

u8 IsPreciousCardsFromBeyondActiveForDuelist(u8 duelist);
u8 IsActivatedPreciousCardsFromBeyondZone(const struct DuelCard *zone);
void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);
void EffectPreciousCardsFromBeyond(void);

#endif // GUARD_PRECIOUS_CARDS_FROM_BEYOND_H
