#ifndef GUARD_POWER_BOND_H
#define GUARD_POWER_BOND_H

#include "global.h"

extern u16 gPowerBondAtkBonus[];
extern u16 gPowerBondEndPhaseBurn;

void PowerBond_OnFusionSummoned(u16 resultId);
void PowerBond_ClearAtkBonusForZone(const struct DuelCard *zone);
void PowerBond_ClearState(void);
void ApplyPowerBondAtkBonusToCardInfo(const struct DuelCard *zone);
void TryApplyPowerBondEndPhaseBurn(void);

#endif // GUARD_POWER_BOND_H
