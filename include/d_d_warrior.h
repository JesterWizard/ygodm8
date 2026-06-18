#ifndef GUARD_D_D_WARRIOR_H
#define GUARD_D_D_WARRIOR_H

#define D_D_WARRIOR_PENDING_NONE 0xFF

extern u8 gPendingDDWarriorWarriorRow;
extern u8 gPendingDDWarriorWarriorCol;
extern u8 gPendingDDWarriorOtherRow;
extern u8 gPendingDDWarriorOtherCol;

void ApplyDDWarriorBattleEffect(void);
void ResolveDDWarriorBattleEffect(void);
void ClearDDWarriorPending(void);

#endif // GUARD_D_D_WARRIOR_H
