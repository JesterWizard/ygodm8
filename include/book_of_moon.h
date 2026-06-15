#ifndef GUARD_BOOK_OF_MOON_H
#define GUARD_BOOK_OF_MOON_H

#define DUEL_CURSOR_BOOK_OF_MOON_TARGET 13

u8 IsBookOfMoonCard(u16 cardId);
u8 FieldHasBookOfMoonTarget(u8 originFixedRow, u8 originFixedCol);
void BeginBookOfMoonTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectBookOfMoonTarget(void);
void CancelBookOfMoonTargeting(void);
void EffectBookOfMoon(void);

#endif // GUARD_BOOK_OF_MOON_H
