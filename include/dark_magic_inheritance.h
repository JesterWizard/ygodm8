#ifndef GUARD_DARK_MAGIC_INHERITANCE_H
#define GUARD_DARK_MAGIC_INHERITANCE_H

#include "gba/types.h"

/* EffectOpt-backed OPT; EffectEvent_OnTurnBoundary clears the shared state. */
u8 DarkMagicInheritance_IsOptUsed(void);
void DarkMagicInheritance_MarkOptUsed(void);

#endif /* GUARD_DARK_MAGIC_INHERITANCE_H */
