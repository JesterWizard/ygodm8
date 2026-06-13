#ifndef GUARD_GRAVITY_BIND_H
#define GUARD_GRAVITY_BIND_H

#define TRAP_GRAVITY_BIND 27

u8 IsActivatedGravityBindZone(const struct DuelCard *zone);
u8 IsGravityBindActiveOnField(void);
u8 GravityBind_ShouldActivateTrapOnAttack(const struct DuelCard *trapZone, u16 attackerCardId);
u8 GravityBind_CanMonsterAttack(u16 cardId);
void EffectGravityBind(void);

#endif // GUARD_GRAVITY_BIND_H
