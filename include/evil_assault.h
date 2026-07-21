#ifndef GUARD_EVIL_ASSAULT_H
#define GUARD_EVIL_ASSAULT_H

#include "gba/types.h"

/* Wire into the Extra Deck special-summon gate. */
u8 EvilAssault_BlocksExtraDeckSpecialSummon(u16 cardId);
/* Wire into EffectEvent_OnTurnBoundary. */
void EvilAssault_OnTurnBoundary(void);
/* Call from the EVIL_ASSAULT-to-GY path to enforce "except the turn sent." */
void EvilAssault_NotifySentToGraveyard(void);
/* Register in the own-GY ignition table. */
u8 CanActivateEvilAssaultGy(u8 fixedDuelist, u8 gyIndex);
void ActivateEvilAssaultGy(u8 fixedDuelist, u8 gyIndex);

#endif /* GUARD_EVIL_ASSAULT_H */
