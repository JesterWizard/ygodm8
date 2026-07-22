#ifndef GUARD_ARCHLORD_KRISTYA_H
#define GUARD_ARCHLORD_KRISTYA_H

#include "global.h"

extern u8 gArchlordKristyaEffectSummon;

u8 ArchlordKristya_IsSpecialSummonLocked(void);
u8 ArchlordKristya_BlocksSpecialSummon(u16 cardId);
u8 ArchlordKristya_ShouldBlockFieldPlacement(u16 cardId, u8 tributesPaid);
u8 CanSpecialSummonArchlordKristyaFromHand(u8 handZone);
u8 TrySpecialSummonArchlordKristyaFromHand(u8 handZone);
u8 ArchlordKristya_TrySendFaceUpFieldToDeckTop(struct DuelCard *zone, u8 turnDuelist);
void ClearArchlordKristyaState(void);

#endif // GUARD_ARCHLORD_KRISTYA_H
