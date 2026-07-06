#ifndef GUARD_TRIBUTE_DOLL_H
#define GUARD_TRIBUTE_DOLL_H

#include "global.h"

#define DUEL_CURSOR_TRIBUTE_DOLL_TARGET 43

u8 CanActivateTributeDoll(void);
void BeginTributeDollTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectTributeDollTarget(void);
void CancelTributeDollTargeting(void);

#endif // GUARD_TRIBUTE_DOLL_H
