#ifndef GUARD_GUARDIAN_ANGEL_JOAN_H
#define GUARD_GUARDIAN_ANGEL_JOAN_H

#define GUARDIAN_ANGEL_JOAN_PENDING_NONE 0xFF

extern u8 gPendingGuardianAngelJoanDuelist;
extern u16 gPendingGuardianAngelJoanDestroyedAtk;

void ApplyGuardianAngelJoanBattleEffect(void);
void ResolveGuardianAngelJoanBattleEffect(void);
void ClearGuardianAngelJoanPending(void);

#endif
