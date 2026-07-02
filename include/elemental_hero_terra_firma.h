#ifndef ELEMENTAL_HERO_TERRA_FIRMA_H
#define ELEMENTAL_HERO_TERRA_FIRMA_H

#define DUEL_CURSOR_TERRA_FIRMA_TARGET 35

unsigned char CanActivateElementalHeroTerraFirma(void);
void ActivateElementalHeroTerraFirmaEffect(void);
void TrySelectElementalHeroTerraFirmaTarget(void);
void CancelElementalHeroTerraFirmaTargeting(void);
u8 ElementalHeroTerraFirma_RevealsAllyZone(u8 fixedRow, u8 fixedCol);

#endif // ELEMENTAL_HERO_TERRA_FIRMA_H
