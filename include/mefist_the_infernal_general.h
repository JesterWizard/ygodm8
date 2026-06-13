#ifndef GUARD_MEFIST_THE_INFERNAL_GENERAL_H
#define GUARD_MEFIST_THE_INFERNAL_GENERAL_H

#include "global.h"

#define MEFIST_DISCARD_PENDING_NONE 0xFF

extern u8 gPendingMefistDiscardDuelist;

void ApplyMefistTheInfernalGeneralPiercingBattleEffect(void);
void ApplyMefistTheInfernalGeneralDiscardBattleEffect(void);
void ResolveMefistTheInfernalGeneralDiscardBattleEffect(void);
void ClearMefistDiscardPending(void);

#endif // GUARD_MEFIST_THE_INFERNAL_GENERAL_H
