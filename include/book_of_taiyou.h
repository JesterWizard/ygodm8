#ifndef GUARD_BOOK_OF_TAIYOU_H
#define GUARD_BOOK_OF_TAIYOU_H

#define DUEL_CURSOR_BOOK_OF_TAIYOU_TARGET 31

u8 IsBookOfTaiyouCard(u16 cardId);
u8 FieldHasBookOfTaiyouTarget(u8 originFixedRow, u8 originFixedCol);
void BeginBookOfTaiyouTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectBookOfTaiyouTarget(void);
void CancelBookOfTaiyouTargeting(void);
void EffectBookOfTaiyou(void);

#endif // GUARD_BOOK_OF_TAIYOU_H
