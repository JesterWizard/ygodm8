#ifndef GUARD_LIGHT_END_DRAGON_H
#define GUARD_LIGHT_END_DRAGON_H

#define DUEL_CURSOR_LIGHT_END_DRAGON_TARGET 47

#define MAX_DUEL_BOARD_CELLS 20
extern s16 gLightEndDragonDefDelta[MAX_DUEL_BOARD_CELLS];

void TrySelectLightEndDragonTarget(void);
void CancelLightEndDragonTargeting(void);
void ClearLightEndDragonDefDeltas(void);
void ApplyLightEndDragonDefDeltaToCardInfo(const struct DuelCard *zone);

#endif // GUARD_LIGHT_END_DRAGON_H
