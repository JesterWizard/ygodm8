#ifndef GUARD_OJAMA_TRIO_H
#define GUARD_OJAMA_TRIO_H

#include "global.h"

void TryActivateOjamaTrioOnOpponentTurnStart(void);
u8 OjamaTrioZoneIsMonsterForm(const struct DuelCard *zone);
void ApplyOjamaTrioCardInfoOverridesForStatMod(struct StatMod *ptr);
void ApplyOjamaTrioDestructionDamage(struct DuelCard *zone);
void SendOjamaTrioZoneToGraveyardIfNeeded(struct DuelCard *zone, u8 turn);

#endif // GUARD_OJAMA_TRIO_H
