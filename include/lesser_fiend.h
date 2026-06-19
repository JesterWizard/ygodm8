#ifndef GUARD_LESSER_FIEND_H
#define GUARD_LESSER_FIEND_H

#define LESSER_FIEND_PENDING_NONE 0xFF

extern u8 gPendingLesserFiendBanishRow;
extern u8 gPendingLesserFiendBanishCol;

void ApplyLesserFiendBattleEffect(void);
void ResolveLesserFiendBattleEffect(void);
void ClearLesserFiendPending(void);

#endif
