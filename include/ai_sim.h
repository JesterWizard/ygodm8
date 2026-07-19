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
void AiSimBatchGraveyardSave(void);
void AiSimBatchGraveyardRestore(void);
u8 AiSimFieldNeedsPermanentRescan(void);
void AiSimScanBoard(void);
u8 AiSimHandHasPermanentCard(void);
u8 AiSimQuickReject(u16 actionIndex);
void AiSimMarkLethalFound(void);
u8 AiSimRejectAfterLethal(u16 action);
u8 AiSimTryRecordLightAttack(u16 actionIndex);
u8 AiSimFullSimBudget(void);
void AiSimRecordPriority(u16 actionIndex, u32 priority);
void AiClearCommandData(void);
void AiInitCommandData(u16 index);

#endif
