#ifndef GUARD_D_BURST_H
#define GUARD_D_BURST_H

#include "gba/types.h"

struct DuelCard;

u8 CanActivateD_BURST(void);
u8 D_Burst_CanActivateGyBattle(struct DuelCard *attacker, u8 fixedDuelist);
void D_Burst_ActivateGyBattle(struct DuelCard *attacker, u8 fixedDuelist);

#endif /* GUARD_D_BURST_H */
