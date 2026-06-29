#ifndef GUARD_EXPANDED_GRAVEYARD_H
#define GUARD_EXPANDED_GRAVEYARD_H

#include "gba/types.h"

#define EXPANDED_GRAVEYARD_CAPACITY 40

void GraveyardExpand_Init(void);
u8 GraveyardExpand_IsEnabled(void);
void GraveyardExpand_PushFixed(u8 fixedDuelist, u16 cardId);
void GraveyardExpand_PushTurn(u8 turnDuelist, u16 cardId);
u16 GraveyardExpand_PopFixed(u8 fixedDuelist);
u16 GraveyardExpand_PopTurn(u8 turnDuelist);
u8 GraveyardExpand_GetCount(u8 fixedDuelist);
u16 GraveyardExpand_GetCardAt(u8 fixedDuelist, u8 index);

u16 GraveyardExpand_RemoveAtFixed(u8 fixedDuelist, u8 index);
u16 GraveyardExpand_RemoveAtTurn(u8 turnDuelist, u8 index);

void GraveyardExpand_SyncLegacyTop(u8 fixedDuelist);
void GraveyardExpand_SyncAllLegacyTops(void);
void GraveyardExpand_SyncFromTurnStart(void);
void GraveyardExpand_CopyStacks(u16 *dst);
void GraveyardExpand_LoadStacks(const u16 *src);
void GraveyardExpand_RefreshDisplay(void);
void GraveyardExpand_ClearOpponentAfterSimIfFirstTurn(void);

#endif
