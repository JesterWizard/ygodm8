#ifndef GUARD_NEO_SPACIAN_GRAND_MOLE_H
#define GUARD_NEO_SPACIAN_GRAND_MOLE_H

#define NEO_SPACIAN_GRAND_MOLE_PENDING_NONE 0xFF

extern u8 gPendingNeoSpacianGrandMoleRow0;
extern u8 gPendingNeoSpacianGrandMoleCol0;
extern u8 gPendingNeoSpacianGrandMoleRow1;
extern u8 gPendingNeoSpacianGrandMoleCol1;

void ApplyNeoSpacianGrandMoleBattleEffect(void);
void ResolveNeoSpacianGrandMoleBattleEffect(void);
void ClearNeoSpacianGrandMolePending(void);

#endif
