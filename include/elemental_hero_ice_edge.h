#ifndef GUARD_ELEMENTAL_HERO_ICE_EDGE_H
#define GUARD_ELEMENTAL_HERO_ICE_EDGE_H

#include "global.h"

#define ELEMENTAL_HERO_ICE_EDGE_BATTLED_NONE 0xFF

extern u8 gElementalHeroIceEdgeBattledRow;
extern u8 gElementalHeroIceEdgeBattledCol;

u8 CanElementalHeroIceEdgeAttackDirectly(const struct DuelCard *zone);
void ClearElementalHeroIceEdgeDirectAttackFlags(void);

unsigned char CanActivateElementalHeroIceEdge(void);
void ActivateElementalHeroIceEdgeEffect(void);

void ApplyElementalHeroIceEdgeBattleEffect(void);
void ResolveElementalHeroIceEdgeBattleEffect(void);
void ClearElementalHeroIceEdgeBattledPending(void);

#endif // GUARD_ELEMENTAL_HERO_ICE_EDGE_H
