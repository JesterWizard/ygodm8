#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateGiantGermEffect(void)
{
  u8 damageTarget;

  if ((gActiveEffect.turnRow == 6 && WhoseTurn() == DUEL_PLAYER) ||
      (gActiveEffect.turnRow == 7 && WhoseTurn() != DUEL_PLAYER))
    damageTarget = INACTIVE_DUELIST;
  else
    damageTarget = ACTIVE_DUELIST;

  if (Duel_ChangeLp(damageTarget, -500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (gActiveEffect.turnRow == 6)
    GetGraveCardAndClearGrave(ACTIVE_DUELIST);
  else
    GetGraveCardAndClearGrave(INACTIVE_DUELIST);

  Duel_ShowEffectText(GIANT_GERM);
}
