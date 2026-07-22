#ifndef GUARD_AZURE_EYES_SILVER_DRAGON_H
#define GUARD_AZURE_EYES_SILVER_DRAGON_H

#include "global.h"

u8 AzureEyesSilverDragon_PreventsBattleDestroy(const struct DuelCard *zone);
u8 AzureEyesSilverDragon_PreventsDestroy(const struct DuelCard *zone);
void TryApplyAzureEyesSilverDragonStandby(void);
void TryClearAzureEyesSilverDragonProtectEndPhase(void);

#endif /* GUARD_AZURE_EYES_SILVER_DRAGON_H */
