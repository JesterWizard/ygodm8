#ifndef GUARD_DE_FUSION_H
#define GUARD_DE_FUSION_H

#define DUEL_CURSOR_DE_FUSION_TARGET 32

u8 IsDeFusionCard(u16 cardId);
u8 FieldHasDeFusionTarget(u8 originFixedRow, u8 originFixedCol);
void BeginDeFusionTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectDeFusionTarget(void);
void CancelDeFusionTargeting(void);
void EffectDeFusion(void);

#endif // GUARD_DE_FUSION_H
