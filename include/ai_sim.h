#ifndef GUARD_AI_SIM_H
#define GUARD_AI_SIM_H

#include "gba/types.h"

extern u8 gAiSimInBatch;
extern u8 gHideEffectText;

static inline u8 AiSimSuppressesGraveyardMutations(void)
{
  return gAiSimInBatch;
}

void AiSimulateAllCandidateActions(void);
void AiSimulateAllCandidateActionsFast(void);
void AiSimBatchGraveyardSave(void);
void AiSimBatchGraveyardRestore(void);
u8 AiSimFieldNeedsPermanentRescan(void);
void AiClearCommandData(void);
void AiInitCommandData(u16 index);

#endif
