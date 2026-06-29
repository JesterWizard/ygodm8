#ifndef GUARD_ELEMENTAL_HERO_WILDEDGE_H
#define GUARD_ELEMENTAL_HERO_WILDEDGE_H

#include "global.h"

void ClearElementalHeroWildedgeState(void);
unsigned char CanActivateElementalHeroWildedge(void);
void ActivateElementalHeroWildedgeEffect(void);
void TryUnlockElementalHeroWildedgeForNextAttack(struct DuelCard *attacker,
                                                 struct DuelCard *defender);

#endif
