#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void ShuffleDeckRange(u8 duelist, u8 start, u8 end)
{
  u8 size;
  int i;

  if (end <= start)
    return;

  size = end - start;
  if (size <= 1)
    return;

  for (i = 0; i < 200; i++) {
    u8 indexA = RandRangeU8(0, size - 1);
    u8 indexB = RandRangeU8(0, size - 1);
    u16 temp = gDuelDecks[duelist].cards[start + indexA];

    gDuelDecks[duelist].cards[start + indexA] = gDuelDecks[duelist].cards[start + indexB];
    gDuelDecks[duelist].cards[start + indexB] = temp;
  }
}

APPEND_TEXT void EffectReload(void)
{
  u8 duelist = ACTIVE_DUELIST;
  u8 i;
  u8 handCount = 0;
  u16 handCards[MAX_ZONES_IN_ROW];
  u8 deckSize;
  u8 cardsDrawn;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[duelist][i]->id == CARD_NONE)
      continue;

    handCards[handCount++] = gTurnHands[duelist][i]->id;
    ClearZone(gTurnHands[duelist][i]);
  }

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], duelist, FALSE);

  if (handCount == 0) {
    Duel_ShowEffectText(RELOAD);
    return;
  }

  deckSize = NumCardsInDeck(duelist);
  cardsDrawn = gDuelDecks[duelist].cardsDrawn;

  if (cardsDrawn >= handCount)
    gDuelDecks[duelist].cardsDrawn = cardsDrawn - handCount;
  else
    gDuelDecks[duelist].cardsDrawn = 0;

  for (i = 0; i < handCount; i++)
    gDuelDecks[duelist].cards[gDuelDecks[duelist].cardsDrawn + i] = handCards[i];

  ShuffleDeckRange(duelist, gDuelDecks[duelist].cardsDrawn, deckSize);

  if (Duel_DrawCards(duelist, handCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(RELOAD);
}
