#ifndef GUARD_COURT_OF_JUSTICE_H
#define GUARD_COURT_OF_JUSTICE_H

#include "global.h"

struct DuelCard;

u8 CanActivateCourtOfJusticeIgnition(struct DuelCard *zone);
u8 CanUseCourtOfJusticeHandIgnition(void);
u8 CourtOfJustice_HandSlotMayIgnition(u8 handSlot);
u8 TryConsumeCourtOfJusticeIgnitionPlacement(void);
void CourtOfJustice_FinishHandPlacement(struct DuelCard *zone);
void EffectCourtOfJustice(void);
void CourtOfJustice_RefreshHandUnlocks(void);
void TryUnlockHandForCourtOfJusticeIgnition(void);
void TryEnableCourtOfJusticeIgnitionAfterPlacement(void);
void CourtOfJustice_ResetTurnState(void);

#endif // GUARD_COURT_OF_JUSTICE_H
