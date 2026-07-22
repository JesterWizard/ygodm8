#ifndef GUARD_HARPIE_LADY_ELEGANCE_LOCK_H
#define GUARD_HARPIE_LADY_ELEGANCE_LOCK_H

void HarpieLadyElegance_MarkWindOnlyLock(u8 turnDuelist);
void HarpieLadyElegance_ClearOnTurnBoundary(void);
u8 HarpieLadyElegance_BlocksSpecialSummon(u8 turnDuelist, u16 cardId);

#endif /* GUARD_HARPIE_LADY_ELEGANCE_LOCK_H */
