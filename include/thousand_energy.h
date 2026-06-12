#ifndef GUARD_THOUSAND_ENERGY_H
#define GUARD_THOUSAND_ENERGY_H

#include "gba/types.h"

extern u8 gThousandEnergyDestroyMask;
extern u8 gThousandEnergyFixedMonsterRow;

void EffectThousandEnergy(void);
void DestroyThousandEnergyMonstersAtEndOfTurn(void);
void ResetThousandEnergyState(void);

#endif
