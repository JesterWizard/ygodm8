#ifndef GUARD_REMOVED_FROM_PLAY_H
#define GUARD_REMOVED_FROM_PLAY_H

#include "gba/types.h"

#define REMOVED_FROM_PLAY_CAPACITY 40

void RemovedFromPlay_Init(void);
u8 RemovedFromPlay_IsEnabled(void);
void RemovedFromPlay_PushFixed(u8 fixedDuelist, u16 cardId);
void RemovedFromPlay_PushZone(struct DuelCard *zone);
u8 RemovedFromPlay_GetCount(u8 fixedDuelist);
u16 RemovedFromPlay_GetCardAt(u8 fixedDuelist, u8 index);
u8 RemovedFromPlay_RemoveAt(u8 fixedDuelist, u8 index);
u8 RemovedFromPlay_RemoveMatching(u8 fixedDuelist, u16 cardId);

void Duel_RemovedFromPlayViewer_Open(u8 fixedDuelist);

#endif
