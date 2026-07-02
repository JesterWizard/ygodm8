#ifndef ELEMENTAL_HERO_GREAT_TORNADO_H
#define ELEMENTAL_HERO_GREAT_TORNADO_H

#include "riryoku.h"

void ElementalHeroGreatTornado_OnFusionSummoned(void);
void ApplyGreatTornadoStatHalving(const struct DuelCard *zone);
void ElementalHeroGreatTornado_OnZoneCleared(const struct DuelCard *zone);
u8 ElementalHeroGreatTornado_IsActiveOnField(void);
void ElementalHeroGreatTornado_RefreshStatsIfActive(void);
void TryElementalHeroGreatTornadoOnMonsterPlacement(struct DuelCard *zone);

#endif // ELEMENTAL_HERO_GREAT_TORNADO_H
