#ifndef GUARD_RING_OF_DESTRUCTION_H
#define GUARD_RING_OF_DESTRUCTION_H

#define DUEL_CURSOR_RING_OF_DESTRUCTION_TARGET 14

u8 IsRingOfDestructionCard(u16 cardId);
u8 CanActivateRingOfDestruction(void);
u8 FieldHasRingOfDestructionTarget(u8 originFixedRow, u8 originFixedCol);
void BeginRingOfDestructionTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectRingOfDestructionTarget(void);
void CancelRingOfDestructionTargeting(void);
void TryRingOfDestructionOnMonsterPlacement(struct DuelCard *zone);
void RingOfDestruction_CheckAfterFieldChange(void);
void EffectRingOfDestruction(void);

#endif // GUARD_RING_OF_DESTRUCTION_H
