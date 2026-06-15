#ifndef GUARD_BERSERK_GORILLA_H
#define GUARD_BERSERK_GORILLA_H

#include "global.h"

u8 BerserkGorilla_CannotUseDefensePosition(u16 cardId);
void TryEnforceBerserkGorillaOnMonsterPlacement(struct DuelCard *zone);
unsigned char ShouldActivateBerserkGorilla(void);
void ActivateBerserkGorilla(void);

#endif // GUARD_BERSERK_GORILLA_H
