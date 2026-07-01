#ifndef GUARD_ELEMENTAL_HERO_NEOS_ALIUS_H
#define GUARD_ELEMENTAL_HERO_NEOS_ALIUS_H

#include "duel.h"

#define NEOS_ALIUS_BOARD_CELL_COUNT (4 * MAX_ZONES_IN_ROW)

void ElementalHeroNeosAlius_Reset(void);
void ElementalHeroNeosAlius_ClearZone(struct DuelCard *zone);
u8 ElementalHeroNeosAlius_IsAwakened(struct DuelCard *zone);
u16 ElementalHeroNeosAlius_GetEffectiveCardId(struct DuelCard *zone);
void ElementalHeroNeosAlius_ApplyCardInfoOverrides(struct DuelCard *zone);
void ElementalHeroNeosAlius_ApplyCardInfoOverridesFromContext(u16 cardId);
unsigned char CanActivateElementalHeroNeosAlius(void);
void ActivateElementalHeroNeosAliusEffect(void);

#endif
