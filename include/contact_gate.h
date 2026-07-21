#ifndef GUARD_CONTACT_GATE_H
#define GUARD_CONTACT_GATE_H

#include "effect.h"
#include "gba/types.h"

u8 CanActivateCONTACT_GATE(void);
u8 CanActivateContactGateGy(u8 fixedDuelist, u8 gyIndex);
void ActivateContactGateGy(u8 fixedDuelist, u8 gyIndex);
void ContactGate_NotifyNeosFusionReturnedToExtra(u8 controllerFixedDuelist);
u8 ContactGate_FusionListsElementalHeroNeos(u16 cardId);
void ContactGate_ArmExtraDeckFusionOnlyLock(void);
u8 ContactGate_BlocksExtraDeckSpecialSummon(u16 cardId);
void ContactGate_OnTurnBoundary(void);
u8 Cond_ContactGateOnFusionReturn(struct EffectCtx *ctx);
enum DuelActionResult Op_ContactGateOnFusionReturn(struct EffectCtx *ctx);

#endif /* GUARD_CONTACT_GATE_H */
