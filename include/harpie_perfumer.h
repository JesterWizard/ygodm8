#ifndef GUARD_HARPIE_PERFUMER_H
#define GUARD_HARPIE_PERFUMER_H

#include "global.h"

u8 HarpiePerfumer_TreatsNameAsHarpieLady(const struct DuelCard *zone);
u8 HarpiePerfumer_TryAddSistersSpellTrapFromDeck(u8 turnDuelist);
u8 Harpie_MentionsHarpieLadySisters(u16 cardId);
void HarpieOracle_ArmEndPhasePending(u8 turnDuelist);
void HarpieOracle_ClearOnTurnBoundary(void);
void TryApplyHarpieOracleEndPhase(void);

#endif /* GUARD_HARPIE_PERFUMER_H */
