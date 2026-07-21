#ifndef GUARD_HARPIE_LADY_PHOENIX_FORMATION_H
#define GUARD_HARPIE_LADY_PHOENIX_FORMATION_H

#include "gba/types.h"

u8 CanActivateHARPIE_LADY_PHOENIX_FORMATION(void);

/* Wire only into Main/Extra Deck Special Summon and Battle Phase entry gates. */
u8 HarpieLadyPhoenixFormation_CannotSpecialSummonFromMainOrExtraDeck(void);
u8 HarpieLadyPhoenixFormation_CannotConductBattlePhase(void);

#endif /* GUARD_HARPIE_LADY_PHOENIX_FORMATION_H */
