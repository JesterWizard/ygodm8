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

#endif
