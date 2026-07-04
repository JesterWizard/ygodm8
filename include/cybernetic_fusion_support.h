#ifndef GUARD_CYBERNETIC_FUSION_SUPPORT_H
#define GUARD_CYBERNETIC_FUSION_SUPPORT_H

#include "global.h"

extern u8 gCyberneticFusionSupportActive;

u8 IsCyberneticFusionSupportActive(void);
void ActivateCyberneticFusionSupportForTurn(void);
void ClearCyberneticFusionSupport(void);

#endif // GUARD_CYBERNETIC_FUSION_SUPPORT_H
