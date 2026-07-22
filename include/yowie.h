#ifndef GUARD_YOWIE_H
#define GUARD_YOWIE_H

#include "gba/types.h"

#define YOWIE_SKIP_DRAW_NONE 0xFF

extern u8 gYowieSkipDrawDuelist;

void ResetYowieSkipDraw(void);
u8 ShouldSkipDrawPhaseForYowie(u8 turn);
void ConsumeYowieSkipDraw(u8 turn);
void Yowie_MarkOpponentSkipDraw(u8 turnDuelist);

#endif /* GUARD_YOWIE_H */
