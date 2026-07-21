#ifndef GUARD_HYSTERIC_SIGN_H
#define GUARD_HYSTERIC_SIGN_H

#include "gba/types.h"

/* Call when a HYSTERIC_SIGN card is sent from its owner's hand or field to GY. */
void HystericSign_NotifySentFromHandOrField(u8 fixedDuelist, u16 cardId);

/* Wire once at each End Phase. */
void HystericSign_TryResolveEndPhase(void);

#endif /* GUARD_HYSTERIC_SIGN_H */
