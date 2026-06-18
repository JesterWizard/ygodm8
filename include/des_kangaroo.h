#ifndef GUARD_DES_KANGAROO_H
#define GUARD_DES_KANGAROO_H

#define DES_KANGAROO_PENDING_NONE 0xFF

extern u8 gPendingDesKangarooAttackerRow;
extern u8 gPendingDesKangarooAttackerCol;

void ApplyDesKangarooBattleEffect(void);
void ResolveDesKangarooBattleEffect(void);
void ClearDesKangarooPending(void);

#endif // GUARD_DES_KANGAROO_H
