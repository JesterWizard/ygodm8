#include "global.h"
#include "common-chax.h"
#include "mini_card.h"

void ActivateHourglassOfLifeEffect(void)
{
  u8 i;

  /* Active duelist monster row (turn-relative), not gMonEffect.row: player flip
   * uses fixed-row cursor coords; AI flip uses turn-row coords in sub_800E8B4. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      IncrementPermStage(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]);

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(1000);
  else
    SetOpponentLifePointsToSubtract(1000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = HOURGLASS_OF_LIFE;
    ActivateCardEffectText();
  }

  RefreshFieldMonsterStatOverlays();
}
