#ifndef GUARD_RAREGOLD_ARMOR_H
#define GUARD_RAREGOLD_ARMOR_H

#include "global.h"
#include "duel.h"

struct DuelCard *RaregoldArmor_GetForcedAttackTarget(u8 defenderDuelist);
u8 RaregoldArmor_CanBeAttacked(struct DuelCard *zone);
u8 RaregoldArmor_BlocksDirectAttack(u8 defenderDuelist);
void EffectRaregoldArmor(void);

#endif // GUARD_RAREGOLD_ARMOR_H
