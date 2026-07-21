#ifndef GUARD_FUSION_DESTINY_H
#define GUARD_FUSION_DESTINY_H

#include "gba/types.h"

struct DuelCard;

void FusionDestiny_StampSummonedZone(struct DuelCard *zone);
void FusionDestiny_ClearStampedZone(const struct DuelCard *zone);
void TryApplyFusionDestinyEndPhase(void);
void FusionDestiny_MarkDarkHeroSpecialSummonLock(void);
void FusionDestiny_ClearDarkHeroSpecialSummonLock(void);
u8 FusionDestiny_BlocksSpecialSummon(u16 cardId);

#endif /* GUARD_FUSION_DESTINY_H */
