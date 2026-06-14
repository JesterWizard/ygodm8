#ifndef GUARD_NEGATIVE_ENERGY_H
#define GUARD_NEGATIVE_ENERGY_H

#define DUEL_CURSOR_NEGATIVE_ENERGY_TARGET 12

u8 IsNegativeEnergyCard(u16 cardId);
u8 FieldHasNegativeEnergyTarget(u8 originFixedRow, u8 originFixedCol);
void BeginNegativeEnergyTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectNegativeEnergyTarget(void);
void CancelNegativeEnergyTargeting(void);
void EffectNegativeEnergy(void);

#endif // GUARD_NEGATIVE_ENERGY_H
