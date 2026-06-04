#ifndef GUARD_RIRYOKU_H
#define GUARD_RIRYOKU_H

#define DUEL_CURSOR_RIRYOKU_SOURCE 6
#define DUEL_CURSOR_RIRYOKU_RECIPIENT 7

#define MAX_DUEL_BOARD_CELLS (4 * MAX_ZONES_IN_ROW)

extern s16 gRiryokuAtkDelta[MAX_DUEL_BOARD_CELLS];
extern struct DuelCard *gSetFinalStatZone;
extern u8 gRiryokuSourceRow;
extern u8 gRiryokuSourceCol;
extern u8 gRiryokuRecipientRow;
extern u8 gRiryokuRecipientCol;

u8 IsRiryokuCard(u16 cardId);
u8 FieldHasRiryokuTarget(u8 originFixedRow, u8 originFixedCol);
void BeginRiryokuTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectRiryokuSourceTarget(void);
void TrySelectRiryokuRecipientTarget(void);
void CancelRiryokuTargeting(void);
void EffectRiryoku(void);
void ClearRiryokuAtkDeltaForZone(const struct DuelCard *zone);
void ClearAllRiryokuAtkDeltas(void);
void ApplyRiryokuAtkDeltaToCardInfo(const struct DuelCard *zone);

#endif // GUARD_RIRYOKU_H
