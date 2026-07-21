#ifndef GUARD_REPTILANNE_RAGE_H
#define GUARD_REPTILANNE_RAGE_H

#include "gba/types.h"

struct DuelCard;

u8 CanActivateREPTILANNE_RAGE(void);
void ApplyReptilanneRageAtkBonusToCardInfo(const struct DuelCard *zone);
void ReptilanneRage_OnEquipSentFromField(u8 controllerFixedDuelist);

#endif /* GUARD_REPTILANNE_RAGE_H */
