#ifndef GUARD_VAMPIRE_BABY_H
#define GUARD_VAMPIRE_BABY_H

#include "global.h"

#define VAMPIRE_BABY_PENDING_NONE 0xFF

extern u8 gVampireBabyPendingController;
extern u8 gVampireBabyPendingGraveyardDuelist;
extern u16 gVampireBabyPendingCardId;

void MarkVampireBabyBattleDestruction(u16 playerCardId, u16 opponentCardId, u8 flags);
void ResolveVampireBabyBattleEffect(void);
void ClearVampireBabyPending(void);

#endif
