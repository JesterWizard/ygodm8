#ifndef GUARD_CAIUS_THE_SHADOW_MONARCH_H
#define GUARD_CAIUS_THE_SHADOW_MONARCH_H

#define DUEL_CURSOR_CAIUS_THE_SHADOW_MONARCH_TARGET 25

unsigned char ShouldActivateCaiusTheShadowMonarch(void);
void ActivateCaiusTheShadowMonarch(void);
void TrySelectCaiusTheShadowMonarchTarget(void);
void CancelCaiusTheShadowMonarchTargeting(void);
unsigned char FieldHasCaiusTarget(u8 originFixedRow, u8 originFixedCol);

#endif // GUARD_CAIUS_THE_SHADOW_MONARCH_H
