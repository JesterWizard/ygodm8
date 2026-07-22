#ifndef GUARD_EVIL_HERO_DARK_GAIA_H
#define GUARD_EVIL_HERO_DARK_GAIA_H

#include "global.h"
#include "fusion_duel.h"

extern u16 gEvilHeroDarkGaiaFusionAtk[];

void EvilHeroDarkGaia_StampFusionMaterialAtk(u16 atkSum);
u8 EvilHeroDarkGaia_ApplyDynamicZoneStats(struct DuelCard *zone);
void EvilHeroDarkGaia_ClearBoardStatsForZone(struct DuelCard *zone);
void ApplyEvilHeroDarkGaiaBattleEffect(void);

#endif /* GUARD_EVIL_HERO_DARK_GAIA_H */
