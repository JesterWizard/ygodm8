#ifndef GUARD_FAMILIAR_KNIGHT_H
#define GUARD_FAMILIAR_KNIGHT_H

#include "global.h"

extern u8 gFamiliarKnightBattleDestroyPending;

void MarkFamiliarKnightBattleDestruction(u16 cardId);
unsigned char ShouldActivateFamiliarKnight(void);
void ActivateFamiliarKnight(void);
void ClearFamiliarKnightBattleDestroyPending(void);

#endif
