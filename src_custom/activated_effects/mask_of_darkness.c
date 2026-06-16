#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateMaskOfDarknessEffect(void)
{
  if (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) > 0)
  {
    u8 emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);

    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->id = BEAR_TRAP;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->isFaceUp = FALSE;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->isLocked = FALSE;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->isDefending = FALSE;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->unk4 = 0;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->unkTwo = 0;
    gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]->willChangeSides = FALSE;
    ResetPermStage(gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]);
    ResetTempStage(gTurnZones[ACTIVE_DUELIST_BACKROW][emptyZone]);
  }

  Duel_ShowEffectTextTyped(MASK_OF_DARKNESS, 2);
}
