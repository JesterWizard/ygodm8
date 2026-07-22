#ifndef GUARD_REPTILIANNE_NAGA_H
#define GUARD_REPTILIANNE_NAGA_H

#include "global.h"

struct DuelCard;

u8 ReptilianneNaga_PreventsBattleDestroy(const struct DuelCard *zone);
void TryApplyReptilianneNagaEndPhase(void);
void ApplyReptilianneNagaBattleZeroAtk(void);

#endif /* GUARD_REPTILIANNE_NAGA_H */
