#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_counter_on_resolve.h"

#define SPELL_COUNTER_CAP_STANDARD 3

static void IncrementCounterOnZone(struct DuelCard *zone, u8 cap)
{
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;

  if (zone->unk4 < cap)
    zone->unk4++;
}

void TryIncrementSpellCountersOnSpellResolve(void)
{
  u8 fixedRow;
  u8 col;

  if (IsDuelOver() == TRUE)
    return;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];
      u16 cardId;

      if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
        continue;

      cardId = zone->id;
      if (cardId == ROYAL_MAGICAL_LIBRARY || cardId == SKILLED_DARK_MAGICIAN
          || cardId == SKILLED_WHITE_MAGICIAN)
        IncrementCounterOnZone(zone, SPELL_COUNTER_CAP_STANDARD);
      else if (cardId == MAGICAL_MARIONETTE)
        IncrementCounterOnZone(zone, 126);
    }
  }
}
