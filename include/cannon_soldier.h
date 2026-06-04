#ifndef GUARD_CANNON_SOLDIER_H
#define GUARD_CANNON_SOLDIER_H

#define DUEL_CURSOR_CANNON_SOLDIER_TARGET 5

u8 IsCannonSoldierCard(u16 cardId);
u8 FieldHasCannonSoldierTributeTarget(u8 originFixedRow, u8 originFixedCol);
unsigned char CanActivateCannonSoldier(void);
void ActivateCannonSoldierEffect(void);
void BeginCannonSoldierTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectCannonSoldierTarget(void);
void CancelCannonSoldierTargeting(void);

#endif // GUARD_CANNON_SOLDIER_H
