#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

typedef struct {
  u16 cardId;
  u8 millCount;
} TwilightswornEpMillEntry;

static const TwilightswornEpMillEntry sTwilightswornEpMills[] APPEND_RODATA = {
  { LUMINA_TWILIGHTSWORN_SHAMAN, 3 },
  { JAIN_TWILIGHTSWORN_GENERAL, 2 },
  { RYKO_TWILIGHTSWORN_FIGHTER, 3 },
  { LYLA_TWILIGHTSWORN_ENCHANTRESS, 3 },
};

void TryApplyTwilightswornEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 i;
  u8 col;

  for (i = 0; i < ARRAY_COUNT(sTwilightswornEpMills); i++) {
    u16 cardId = sTwilightswornEpMills[i].cardId;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || !zone->isFaceUp || zone->id != cardId)
        continue;

      Duel_ShowEffectTextTyped(cardId, 2);
      Duel_MillTopDeckCards(turn, sTwilightswornEpMills[i].millCount, TRUE);
      return;
    }
  }
}
