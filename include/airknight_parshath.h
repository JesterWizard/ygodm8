#ifndef GUARD_AIRKNIGHT_PARSHATH_H
#define GUARD_AIRKNIGHT_PARSHATH_H

#define AIRKNIGHT_PARSHATH_DRAW_PENDING_NONE 0xFF

extern u8 gPendingAirknightParshathDrawDuelist;

void ApplyAirknightParshathPiercingBattleEffect(void);
void ApplyAirknightParshathDrawBattleEffect(void);
void ResolveAirknightParshathDrawBattleEffect(void);
void ClearAirknightParshathDrawPending(void);

#endif
