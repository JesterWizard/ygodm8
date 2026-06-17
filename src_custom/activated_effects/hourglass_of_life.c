#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateHourglassOfLifeEffect(void)
{
  /* Active duelist monster row (turn-relative), not gMonEffect.row: player flip
   * uses fixed-row cursor coords; AI flip uses turn-row coords in sub_800E8B4. */
  Duel_IncrementPermStageOnDuelistMonsters(ACTIVE_DUELIST);

  if (Duel_ChangeLp(ACTIVE_DUELIST, -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_RefreshMonsterStatOverlays();
  Duel_ShowEffectTextTyped(HOURGLASS_OF_LIFE, 2);
}
