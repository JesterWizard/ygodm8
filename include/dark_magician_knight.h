#ifndef GUARD_DARK_MAGICIAN_KNIGHT_H
#define GUARD_DARK_MAGICIAN_KNIGHT_H

#define DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET 8

u8 FieldHasDarkMagicianKnightTarget(u8 originFixedRow, u8 originFixedCol);
unsigned char ShouldActivateDarkMagicianKnight(void);
void ActivateDarkMagicianKnight(void);
void BeginDarkMagicianKnightTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectDarkMagicianKnightTarget(void);
void CancelDarkMagicianKnightTargeting(void);

#endif // GUARD_DARK_MAGICIAN_KNIGHT_H
