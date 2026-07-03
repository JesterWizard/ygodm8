#ifndef GUARD_ELEMENTAL_HERO_BLAZEMAN_H
#define GUARD_ELEMENTAL_HERO_BLAZEMAN_H

extern u16 gElementalHeroBlazemanCopySourceId;
extern u8 gElementalHeroBlazemanCopyRow;
extern u8 gElementalHeroBlazemanCopyCol;

void ClearElementalHeroBlazemanTurnState(void);
void ElementalHeroBlazeman_OnZoneCleared(const struct DuelCard *zone);
void TryElementalHeroBlazemanOnMonsterPlacement(struct DuelCard *zone);
u8 ElementalHeroBlazeman_ApplyDynamicZoneStats(struct DuelCard *zone);

unsigned char CanActivateElementalHeroBlazeman(void);
void ActivateElementalHeroBlazemanEffect(void);

#endif // GUARD_ELEMENTAL_HERO_BLAZEMAN_H
