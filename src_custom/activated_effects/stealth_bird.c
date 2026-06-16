#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateStealthBirdEffect(void)
{
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (Duel_ChangeLp(target, -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(STEALTH_BIRD, 2);
}
