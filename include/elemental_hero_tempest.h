#ifndef GUARD_ELEMENTAL_HERO_TEMPEST_H
#define GUARD_ELEMENTAL_HERO_TEMPEST_H

#define ELEMENTAL_HERO_TEMPEST_ZONE_NONE 0xFF

extern u8 gElementalHeroTempestAnchorRow;
extern u8 gElementalHeroTempestAnchorCol;
extern u8 gElementalHeroTempestProtectedRow;
extern u8 gElementalHeroTempestProtectedCol;

unsigned char CanActivateElementalHeroTempest(void);
void ActivateElementalHeroTempestEffect(void);
void ClearElementalHeroTempestProtection(void);
void ElementalHeroTempestSetProtection(u8 anchorRow, u8 anchorCol, u8 protectedRow,
                                       u8 protectedCol);
u8 ElementalHeroTempestProtectsBattleZone(u8 fixedRow, u8 fixedCol);

#endif
