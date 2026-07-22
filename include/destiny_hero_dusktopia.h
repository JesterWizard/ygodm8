#ifndef GUARD_DESTINY_HERO_DUSKTOPIA_H
#define GUARD_DESTINY_HERO_DUSKTOPIA_H

#include "global.h"

#define DESTINY_HERO_DUSKTOPIA_PROTECT_MARK 0x80

u8 DestinyHeroDusktopia_PreventsBattleDestroy(const struct DuelCard *zone);
void ApplyDestinyHeroDusktopiaNoBattleDamage(void);
void TryClearDestinyHeroDusktopiaProtectionEndPhase(void);

#endif /* GUARD_DESTINY_HERO_DUSKTOPIA_H */
