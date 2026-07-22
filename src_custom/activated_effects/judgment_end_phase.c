#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void TryApplyJudgmentEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != JUDGMENT_THE_DRAGON_OF_HEAVEN)
      continue;

    Duel_ShowEffectTextTyped(JUDGMENT_THE_DRAGON_OF_HEAVEN, 9);
    Duel_MillTopDeckCards(ACTIVE_DUELIST, 4, TRUE);
    return;
  }
}
