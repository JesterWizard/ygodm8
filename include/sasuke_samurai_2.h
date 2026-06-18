#ifndef GUARD_SASUKE_SAMURAI_2_H
#define GUARD_SASUKE_SAMURAI_2_H

#include "global.h"

#define SASUKE_SAMURAI_2_LP_COST 800

extern u8 gSasukeSamurai2InactiveBackrowTrapBlock;

u8 SasukeSamurai2_AreInactiveBackrowTrapsBlocked(void);
void SasukeSamurai2_ClearInactiveBackrowTrapBlock(void);
u8 SasukeSamurai2_AllowsFaceUpEffectActivation(u16 cardId);
unsigned char CanActivateSasukeSamurai2(void);
void ActivateSasukeSamurai2Effect(void);

#endif // GUARD_SASUKE_SAMURAI_2_H
