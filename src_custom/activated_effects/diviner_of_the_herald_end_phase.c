#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "diviner_of_the_herald.h"

void TryClearDivinerOfTheHeraldEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone != NULL && zone->id == DIVINER_OF_THE_HERALD)
        zone->unkTwo = 0;
    }
  }
}
