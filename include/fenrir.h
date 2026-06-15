#ifndef GUARD_FENRIR_H
#define GUARD_FENRIR_H

#include "gba/types.h"

#define FENRIR_SKIP_DRAW_NONE 0xFF

extern u8 gFenrirSkipDrawDuelist;

void ResetFenrirSkipDraw(void);
u8 ShouldSkipDrawPhaseForFenrir(u8 turn);
void ConsumeFenrirSkipDraw(u8 turn);
void ApplyFenrirBattleEffect(void);

u8 CanSpecialSummonFenrirFromHand(u8 handZone);
u8 TrySpecialSummonFenrirFromHand(u8 handZone);

#endif
