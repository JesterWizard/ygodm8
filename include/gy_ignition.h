#ifndef GUARD_GY_IGNITION_H
#define GUARD_GY_IGNITION_H

#include "global.h"

/* Thin GY ignition dispatch. Own-GY viewer calls TryAt on A when legal.
 * Resolves by cardId (viewer may sort), first matching activatable GY copy.
 * Returns TRUE if an effect activated (caller should close the viewer). */
u8 GyIgnition_TryAt(u8 fixedDuelist, u16 cardId);

#endif /* GUARD_GY_IGNITION_H */
