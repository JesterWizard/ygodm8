#ifndef GUARD_ELEMENTAL_HERO_GLOW_NEOS_H
#define GUARD_ELEMENTAL_HERO_GLOW_NEOS_H

#include "global.h"

#define ELEMENTAL_HERO_GLOW_NEOS_CANNOT_ATTACK_MARK 0x40
#define ELEMENTAL_HERO_GLOW_NEOS_DIRECT_ATTACK_MARK 0x20

u8 ElementalHeroGlowNeos_CanDeclareAttack(const struct DuelCard *zone);
u8 ElementalHeroGlowNeos_CanAttackDirectly(const struct DuelCard *zone);
void ElementalHeroGlowNeos_ClearTurnMarksAtEndPhase(void);

#endif /* GUARD_ELEMENTAL_HERO_GLOW_NEOS_H */
