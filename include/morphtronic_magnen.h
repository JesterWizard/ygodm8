#ifndef GUARD_MORPHTRONIC_MAGNEN_H
#define GUARD_MORPHTRONIC_MAGNEN_H

#include "global.h"

struct DuelCard *MorphtronicMagnen_GetForcedAttackTarget(u8 defenderDuelist);
u8 MorphtronicMagnen_CanAttackMonsterZone(struct DuelCard *zone);
u8 MorphtronicMagnen_CanSelectAttackTarget(const struct DuelCard *attacker,
                                           const struct DuelCard *defender);

#endif /* GUARD_MORPHTRONIC_MAGNEN_H */
