#ifndef GUARD_ANCIENT_GEAR_ATTACK_LOCK_H
#define GUARD_ANCIENT_GEAR_ATTACK_LOCK_H

#include "global.h"

/* TRUE if this attacker prevents opp Spell/Trap activate on attack declaration. */
u8 AncientGear_AttackerBlocksOppSpellTrap(const struct DuelCard *attacker);

#endif /* GUARD_ANCIENT_GEAR_ATTACK_LOCK_H */
