#ifndef GUARD_DARK_ROOM_OF_NIGHTMARE_H
#define GUARD_DARK_ROOM_OF_NIGHTMARE_H

#include "global.h"

#define DARK_ROOM_PENDING_NONE 0xFF

extern u8 gSuppressDarkRoomDamage;
extern u8 gPendingDarkRoomTarget;

void ClearDarkRoomPending(void);
void TryApplyDarkRoomAfterEffectDamage(u8 targetDuelist);
void ResolveDarkRoomEffect(void);
u8 IsActivatedDarkRoomZone(const struct DuelCard *zone);
void EffectDarkRoomOfNightmare(void);

#endif // GUARD_DARK_ROOM_OF_NIGHTMARE_H
