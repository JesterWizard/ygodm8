#ifndef GUARD_SELF_DESTRUCT_BUTTON_H
#define GUARD_SELF_DESTRUCT_BUTTON_H

#include "gba/types.h"

#define SELF_DESTRUCT_BUTTON_LP_DIFFERENCE 7000

u8 CanActivateSelfDestructButton(void);
u8 IsActivatedSelfDestructButtonZone(const struct DuelCard *zone);
void TryActivateSelfDestructButtonOnOpponentTurnStart(void);

#endif // GUARD_SELF_DESTRUCT_BUTTON_H
