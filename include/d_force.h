#ifndef GUARD_D_FORCE_H
#define GUARD_D_FORCE_H

#include "global.h"

struct DuelCard;

u8 DForce_ShouldBlockDrawPhase(void);
u8 DForce_CanTargetPlasmaByCardEffect(const struct DuelCard *target, u8 effectControllerFixedDuelist);
void ApplyDForcePlasmaAtkBonusToCardInfo(struct DuelCard *zone);
u8 DForce_PreventsPlasmaEffectDestruction(const struct DuelCard *target);
u8 DForce_PlasmaCanAttackAgain(const struct DuelCard *attacker);
void TryUnlockDForcePlasmaForSecondAttack(struct DuelCard *attacker);

#endif /* GUARD_D_FORCE_H */
