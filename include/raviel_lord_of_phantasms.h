#ifndef GUARD_RAVIEL_LORD_OF_PHANTASMS_H
#define GUARD_RAVIEL_LORD_OF_PHANTASMS_H

#include "global.h"

#define RAVIEL_TRIBUTE_COST 3
#define PHANTASM_TOKEN_ATK 1000
#define PHANTASM_TOKEN_DEF 1000
#define PHANTASM_TOKEN_LEVEL 1
#define RAVIEL_TOKEN_PENDING_NONE 0xFF

extern u8 gRavielPendingTokenCount;
extern u8 gRavielTokenSummonDuelist;

u8 CanSpecialSummonRavielLordOfPhantasmsFromHand(u8 handZone);
u8 TrySpecialSummonRavielLordOfPhantasmsFromHand(u8 handZone);
void TryRavielOnOpponentMonsterPlacement(struct DuelCard *zone);
u8 CanActivateRAVIEL_LORD_OF_PHANTASMS(void);
void ActivateRAVIEL_LORD_OF_PHANTASMSEffect(void);

#endif
