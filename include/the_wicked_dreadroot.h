#ifndef THE_WICKED_DREADROOT_H
#define THE_WICKED_DREADROOT_H

#include "card.h"

void ApplyTheWickedDreadrootStatHalving(const struct DuelCard *zone);
void TheWickedDreadroot_OnZoneCleared(const struct DuelCard *zone);
u8 TheWickedDreadroot_IsActiveOnField(void);
void TheWickedDreadroot_RefreshStatsIfActive(void);
void TryTheWickedDreadrootOnMonsterPlacement(struct DuelCard *zone);
void TryTheWickedDreadrootEffectTextOnMonsterPlacement(struct DuelCard *zone);

#endif // THE_WICKED_DREADROOT_H
