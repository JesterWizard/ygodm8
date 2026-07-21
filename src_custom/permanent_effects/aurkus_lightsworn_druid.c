#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "aurkus_lightsworn_druid.h"

#define AURKUS_MILL_COUNT 2

void TryApplyAurkusEndPhase(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);
    u8 turn = Duel_TurnDuelistForFixedDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id != AURKUS_LIGHTSWORN_DRUID || !zone->isFaceUp)
        continue;

      Duel_ShowEffectTextTyped(AURKUS_LIGHTSWORN_DRUID, 8);
      if (Duel_MillTopDeckCards(turn, AURKUS_MILL_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }
}

unsigned char ShouldActivateAURKUS_LIGHTSWORN_DRUID(void)
{
  /* End Phase mill is TryApplyAurkusEndPhase; Lightsworn targeting immunity still
   * needs a targeting gate. No on-summon ignition. */
  return FALSE;
}

void ActivateAURKUS_LIGHTSWORN_DRUID(void)
{
}
