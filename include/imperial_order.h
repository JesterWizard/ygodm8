#ifndef GUARD_IMPERIAL_ORDER_H
#define GUARD_IMPERIAL_ORDER_H

#include "global.h"

#define TRAP_IMPERIAL_ORDER 28

u8 IsImperialOrderActiveOnField(void);
u8 IsImperialOrderNegatingSpell(u16 cardId);
void TryActivateImperialOrderOnSpellChain(void);
void EffectImperialOrder(void);
unsigned char ShouldActivateImperialOrderUpkeep(void);
void ActivateImperialOrderUpkeep(void);

#endif // GUARD_IMPERIAL_ORDER_H
