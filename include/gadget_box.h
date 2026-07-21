#ifndef GUARD_GADGET_BOX_H
#define GUARD_GADGET_BOX_H

#include "duel_helpers.h"

void GadgetBox_ClearTokenState(void);
u8 GadgetBox_HasTokenForFixedDuelist(u8 fixedDuelist);
u8 GadgetBox_BlocksExtraDeckSpecialSummon(u8 fixedDuelist, u16 cardId);
u8 GadgetBox_CanActivateIgnition(struct DuelCard *zone);
enum DuelActionResult GadgetBox_ResolveIgnition(struct DuelCard *zone);

#endif /* GUARD_GADGET_BOX_H */
