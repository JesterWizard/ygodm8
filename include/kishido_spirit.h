#ifndef GUARD_KISHIDO_SPIRIT_H
#define GUARD_KISHIDO_SPIRIT_H

#include "gba/types.h"

struct DuelCard;

u8 IsActivatedKishidoSpiritZone(const struct DuelCard *zone);
u8 IsKishidoSpiritActiveForDuelist(u8 duelist);
void EffectKishidoSpirit(void);

#endif // GUARD_KISHIDO_SPIRIT_H
