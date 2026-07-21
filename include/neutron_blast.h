#ifndef GUARD_NEUTRON_BLAST_H
#define GUARD_NEUTRON_BLAST_H

#include "gba/types.h"

struct DuelCard;

u8 CanActivateNEUTRON_BLAST(void);
void TryUnlockNeutronBlastForExtraAttack(struct DuelCard *attacker);
u8 NeutronBlast_ShouldBlockOpponentEffects(const struct DuelCard *attacker);
void NeutronBlast_ClearDamageStepBlock(void);

#endif /* GUARD_NEUTRON_BLAST_H */
