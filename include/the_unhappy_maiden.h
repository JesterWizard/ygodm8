#ifndef GUARD_THE_UNHAPPY_MAIDEN_H
#define GUARD_THE_UNHAPPY_MAIDEN_H

#define UNHAPPY_MAIDEN_PENDING_PLAYER (1 << 0)
#define UNHAPPY_MAIDEN_PENDING_OPPONENT (1 << 1)

extern u8 gForceActiveTurnEnd;
extern u8 gPendingUnhappyMaiden;

void ApplyTheUnhappyMaidenBattleEffect(void);
void ResolveTheUnhappyMaidenBattleEffect(void);
void EndActiveDuelistTurn(void);

#endif
