#ifndef GUARD_DIVINE_SANCTUARY_H
#define GUARD_DIVINE_SANCTUARY_H

#include "global.h"

struct DuelCard;

u8 IsDivineSanctuaryActive(void);
u8 IsActivatedDivineSanctuaryZone(const struct DuelCard *zone);
int ApplyDivineSanctuaryTributeOverride(u16 cardId, int requiredTributes);
void ApplyDivineSanctuaryFieldStatPenalty(u16 cardId, u16 *atk, u16 *def);
void ApplyDivineSanctuaryFieldStatPenaltyForZone(struct DuelCard *zone);

#endif // GUARD_DIVINE_SANCTUARY_H
