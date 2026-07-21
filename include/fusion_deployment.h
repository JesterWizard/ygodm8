#ifndef GUARD_FUSION_DEPLOYMENT_H
#define GUARD_FUSION_DEPLOYMENT_H

#include "global.h"

u8 FusionDeployment_IsLocked(void);
void FusionDeployment_MarkLocked(void);
void FusionDeployment_ClearOnTurnBoundary(void);

#endif /* GUARD_FUSION_DEPLOYMENT_H */
