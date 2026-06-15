#include "global.h"
#include "common-chax.h"
#include "mini_card.h"

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

void ActivateHourglassOfLifeEffect(void)
{
  u8 i;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  /* ponytail: gTurnZones mirror opponent columns; gFixedZones match field tiles. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];

    if (zone->id != CARD_NONE)
      IncrementPermStage(zone);
  }

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
