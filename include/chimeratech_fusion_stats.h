#ifndef GUARD_CHIMERATECH_FUSION_STATS_H
#define GUARD_CHIMERATECH_FUSION_STATS_H

#include "global.h"

struct DuelCard;

void ChimeratechFusion_StampMaterialCount(struct DuelCard *zone, u8 materialCount);
u8 ChimeratechFortressDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ChimeratechMegafleetDragon_ApplyDynamicZoneStats(struct DuelCard *zone);

#endif /* GUARD_CHIMERATECH_FUSION_STATS_H */
