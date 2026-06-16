#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateNimbleMomongaEffect(void)
{
  u8 healDuelist;

  if ((gActiveEffect.turnRow == 6 && WhoseTurn() == DUEL_PLAYER) ||
      (gActiveEffect.turnRow == 7 && WhoseTurn() != DUEL_PLAYER))
    healDuelist = ACTIVE_DUELIST;
  else
    healDuelist = INACTIVE_DUELIST;

  if (Duel_ChangeLp(healDuelist, 1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (gActiveEffect.turnRow == 6)
    GetGraveCardAndClearGrave(ACTIVE_DUELIST);
  else
    GetGraveCardAndClearGrave(INACTIVE_DUELIST);

  Duel_ShowEffectText(NIMBLE_MOMONGA);
}
