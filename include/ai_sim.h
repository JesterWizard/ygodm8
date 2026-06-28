#ifndef GUARD_AI_SIM_H
#define GUARD_AI_SIM_H

#include "gba/types.h"

extern u8 gAiSimInBatch;

void AiSimulateAllCandidateActions(void);
void AiSimulateAllCandidateActionsFast(void);
u8 AiSimFieldNeedsPermanentRescan(void);
void AiClearCommandData(void);
void AiInitCommandData(u16 index);

#endif
