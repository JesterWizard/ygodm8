#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateHourglassOfLifeEffect(void)
{
  u8 i;

  Duel_ShowEffectTextTyped(HOURGLASS_OF_LIFE, 2);

  /* Active duelist monster row (turn-relative), not gMonEffect.row: player flip
   * uses fixed-row cursor coords; AI flip uses turn-row coords in sub_800E8B4. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      IncrementPermStage(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]);

  if (Duel_ChangeLp(WhoseTurn(), -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

}
