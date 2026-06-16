#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateFireReaperEffect(void)
{
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (Duel_ChangeLp(target, -500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(FIRE_REAPER, 2);
}
