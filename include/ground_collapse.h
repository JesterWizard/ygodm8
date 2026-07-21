#ifndef GUARD_GROUND_COLLAPSE_H
#define GUARD_GROUND_COLLAPSE_H

#include "gba/types.h"

u8 CanActivateGROUND_COLLAPSE(void);

/* Wire into every main-monster-zone placement and empty-slot query. */
u8 GroundCollapse_IsMainMonsterZoneLocked(u8 fixedRow, u8 fixedCol);

#endif /* GUARD_GROUND_COLLAPSE_H */
