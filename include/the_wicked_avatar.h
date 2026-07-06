#ifndef THE_WICKED_AVATAR_H
#define THE_WICKED_AVATAR_H

#include "card.h"

extern u8 gTheWickedAvatarLockFixedDuelist;
extern u8 gTheWickedAvatarLockTurnsRemaining;

void ClearTheWickedAvatarLock(void);
u8 TheWickedAvatar_IsSpellTrapActivationLocked(void);
void TheWickedAvatar_TryDecrementLockAtTurnEnd(void);
u8 TheWickedAvatar_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryTheWickedAvatarOnMonsterPlacement(struct DuelCard *zone);
void FinishTheWickedAvatarTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol);
void TheWickedAvatar_OnZoneCleared(const struct DuelCard *zone);
unsigned char ShouldActivateTheWickedAvatar(void);
void ActivateTheWickedAvatar(void);

#endif // THE_WICKED_AVATAR_H
