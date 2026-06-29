#ifndef GUARD_DARK_MAGICIAN_OF_CHAOS_H
#define GUARD_DARK_MAGICIAN_OF_CHAOS_H

#define DARK_MAGICIAN_OF_CHAOS_PENDING_NONE 0xFF

extern u8 gPendingDarkMagicianOfChaosBanishRow;
extern u8 gPendingDarkMagicianOfChaosBanishCol;

u8 DarkMagicianOfChaosBattleZoneIsPendingBanish(u8 row, u8 col);

void ApplyDarkMagicianOfChaosBattleEffect(void);
void ResolveDarkMagicianOfChaosBattleEffect(void);
void ClearDarkMagicianOfChaosPending(void);

#endif
