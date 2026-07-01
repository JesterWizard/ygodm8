#ifndef GUARD_ELEMENTAL_HERO_ELECTRUM_H
#define GUARD_ELEMENTAL_HERO_ELECTRUM_H

#include "global.h"

void ElementalHeroElectrum_ReturnRemovedMonstersToDecks(void);

u8 ElementalHeroElectrum_ApplyDynamicZoneStats(struct DuelCard *zone);
void ElementalHeroElectrum_OnFusionSummoned(void);

#endif // GUARD_ELEMENTAL_HERO_ELECTRUM_H
