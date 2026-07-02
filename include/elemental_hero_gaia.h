#ifndef GUARD_ELEMENTAL_HERO_GAIA_H
#define GUARD_ELEMENTAL_HERO_GAIA_H

#include "global.h"
#include "riryoku.h"

#define DUEL_CURSOR_ELEMENTAL_HERO_GAIA_TARGET 37

extern s16 gElementalHeroGaiaTargetAtkDelta[MAX_DUEL_BOARD_CELLS];
extern u16 gElementalHeroGaiaBoostCellIndex;
extern u16 gElementalHeroGaiaBoostAmount;

void ElementalHeroGaia_OnFusionSummoned(void);
void TrySelectElementalHeroGaiaTarget(void);
void CancelElementalHeroGaiaTargeting(void);
void ApplyElementalHeroGaiaStatMod(const struct DuelCard *zone);
void ElementalHeroGaia_OnZoneCleared(const struct DuelCard *zone);

#endif
