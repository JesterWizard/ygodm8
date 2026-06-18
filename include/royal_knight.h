#ifndef GUARD_ROYAL_KNIGHT_H
#define GUARD_ROYAL_KNIGHT_H

#define ROYAL_KNIGHT_PENDING_NONE 0xFF

extern u8 gPendingRoyalKnightDuelist;
extern u16 gPendingRoyalKnightDestroyedDef;

void ApplyRoyalKnightBattleEffect(void);
void ResolveRoyalKnightBattleEffect(void);
void ClearRoyalKnightPending(void);

#endif
