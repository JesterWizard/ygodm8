#ifndef GUARD_AI_SIM_H
#define GUARD_AI_SIM_H

#include "gba/types.h"

extern u8 gAiSimInBatch;
extern u8 gHideEffectText;

static inline u8 AiSimSuppressesGraveyardMutations(void)
{
  return gAiSimInBatch || gHideEffectText;
}

void AiSimulateAllCandidateActions(void);
void AiSimulateAllCandidateActionsFast(void);
void AiSimClearSavedGraveyard(void);
void AiSimBeginBatchGraveyardCheckpoint(void);
void AiSimEndBatchGraveyardCheckpoint(void);
u8 AiSimFieldNeedsPermanentRescan(void);
void AiClearCommandData(void);
void AiInitCommandData(u16 index);

#endif
