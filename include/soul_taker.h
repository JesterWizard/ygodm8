#ifndef GUARD_SOUL_TAKER_H
#define GUARD_SOUL_TAKER_H

#define DUEL_CURSOR_SOUL_TAKER_TARGET 11

u8 IsSoulTakerCard(u16 cardId);
u8 FieldHasSoulTakerTarget(u8 originFixedRow, u8 originFixedCol);
void BeginSoulTakerTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectSoulTakerTarget(void);
void CancelSoulTakerTargeting(void);
void EffectSoulTaker(void);

#endif // GUARD_SOUL_TAKER_H
