#ifndef GUARD_YATA_GARASU_H
#define GUARD_YATA_GARASU_H

#include "gba/types.h"

#define YATA_GARASU_SKIP_DRAW_NONE 0xFF

extern u8 gYataGarasuSkipDrawDuelist;

void ResetYataGarasuSkipDraw(void);
u8 ShouldSkipDrawPhaseForYataGarasu(u8 turn);
void ConsumeYataGarasuSkipDraw(u8 turn);
void ApplyYataGarasuBattleEffect(void);

#endif
