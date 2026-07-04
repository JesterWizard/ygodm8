#ifndef GUARD_THE_BIG_SATURN_H
#define GUARD_THE_BIG_SATURN_H

#include "global.h"

#define THE_BIG_SATURN_LP_COST 1000
#define THE_BIG_SATURN_ATK_BOOST_STAGES 2

extern u16 gTheBigSaturnGyDamagePending;
extern u8 gTheBigSaturnGyDamageTurnRow;
extern u8 gTheBigSaturnGyDamageFromField;

void ClearTheBigSaturnPending(void);
void ClearTheBigSaturnAtkBoostAtEndOfTurn(void);
void NoteTheBigSaturnGraveyardSend(struct DuelCard *zone);
u8 TheBigSaturn_PendingGraveyardTurnRow(void);
void TheBigSaturn_PrepareGraveyardScan(u8 turnRow, u16 *cardId);
void TheBigSaturn_TryResolveGyDamage(void);
unsigned char CanActivateTheBigSaturn(void);
void ActivateTheBigSaturnEffect(void);
unsigned char ShouldActivateTheBigSaturn(void);
void ActivateTheBigSaturn(void);

#endif
