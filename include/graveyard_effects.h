#ifndef GUARD_GRAVEYARD_EFFECTS_H
#define GUARD_GRAVEYARD_EFFECTS_H

#include "global.h"

#define PENDING_GRAVEYARD_DRAW_NONE 0xFF

extern u8 gDeferGraveyardDrawBattleResolve;
extern u8 gPendingGraveyardDrawFixedDuelist;
extern u8 gGraveyardSendWasFromField;

void NoteGraveyardMonsterSend(struct DuelCard *zone);
void MarkGraveyardSendFromField(void);
u8 CardTriggersDrawOnFieldDestroy(u16 cardId);
u8 CardDefersGraveyardEffectUntilBattleFinish(u16 cardId);
unsigned char ShouldActivateGraveyardDrawOnDestroy(void);
void ActivateGraveyardDrawOnDestroy(void);
void ResolvePendingGraveyardDrawOnDestroy(void);
void FinishGraveyardDrawBattleResolve(void);

#endif
