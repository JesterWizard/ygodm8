#ifndef GUARD_MORPHTRONIC_STAPLEN_H
#define GUARD_MORPHTRONIC_STAPLEN_H

#include "global.h"

u8 MorphtronicStaplen_PreventsBattleDestroy(const struct DuelCard *zone);
struct DuelCard *MorphtronicStaplen_GetForcedAttackTarget(u8 defenderDuelist);
u8 MorphtronicStaplen_CanAttackMonsterZone(struct DuelCard *zone);

#endif /* GUARD_MORPHTRONIC_STAPLEN_H */
