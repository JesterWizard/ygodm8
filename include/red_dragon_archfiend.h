#ifndef GUARD_RED_DRAGON_ARCHFIEND_H
#define GUARD_RED_DRAGON_ARCHFIEND_H

#include "global.h"

#define RED_DRAGON_ARCHFIEND_PENDING_NONE 0xFF

extern u8 gPendingRedDragonArchfiendFixedRow;
extern u8 gMonstersDeclaredAttackThisTurn[4];

void ApplyRedDragonArchfiendBattleEffect(void);
void ResolveRedDragonArchfiendBattleEffect(void);
void ClearRedDragonArchfiendPending(void);
void ClearRedDragonArchfiendAttackDeclaredMask(void);
void MarkMonsterDeclaredAttackThisTurn(struct DuelCard *zone);
void TryApplyRedDragonArchfiendEndPhaseEffect(void);

#endif
