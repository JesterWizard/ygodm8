#ifndef GUARD_FAIRY_BOX_H
#define GUARD_FAIRY_BOX_H

#include "global.h"

u8 IsActivatedFairyBoxZone(const struct DuelCard *zone);
void MarkFairyBoxJustSet(struct DuelCard *zone);
void AgeFairyBoxSetFlags(void);
unsigned char ShouldActivateFairyBoxTurnEffect(void);
void ActivateFairyBoxTurnEffect(void);
unsigned char ShouldActivateFairyBoxUpkeep(void);
void ActivateFairyBoxUpkeep(void);
void TryApplyFairyBoxToPendingAction(void);

#endif // GUARD_FAIRY_BOX_H
