#ifndef GUARD_SKULL_INVITATION_H
#define GUARD_SKULL_INVITATION_H

#include "global.h"

u8 IsActivatedSkullInvitationZone(const struct DuelCard *zone);
u8 IsSkullInvitationActiveOnField(void);
u8 ShouldSuppressSkullInvitationDamageOnCopy(const struct DuelCard *dst, const struct DuelCard *src);
void TryApplySkullInvitationOnFieldLeave(struct DuelCard *zone);
void TryActivateSkullInvitationOnOpponentTurnStart(void);
void EffectSkullInvitation(void);

#endif // GUARD_SKULL_INVITATION_H
