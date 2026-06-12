#ifndef GUARD_BLOCK_ATTACK_H
#define GUARD_BLOCK_ATTACK_H

#define DUEL_CURSOR_BLOCK_ATTACK_TARGET 9

u8 IsBlockAttackCard(u16 cardId);
u8 FieldHasBlockAttackTarget(u8 originFixedRow, u8 originFixedCol);
void BeginBlockAttackTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectBlockAttackTarget(void);
void CancelBlockAttackTargeting(void);
void EffectBlockAttack(void);

#endif // GUARD_BLOCK_ATTACK_H
