#ifndef GUARD_SASUKE_SAMURAI_3_H
#define GUARD_SASUKE_SAMURAI_3_H

#define SASUKE_SAMURAI_3_DRAW_PENDING_NONE 0xFF
#define SASUKE_SAMURAI_3_TARGET_HAND 7

extern u8 gPendingSasukeSamurai3DrawDuelist;

void ApplySasukeSamurai3BattleEffect(void);
void ResolveSasukeSamurai3BattleEffect(void);
void ClearSasukeSamurai3DrawPending(void);

#endif
