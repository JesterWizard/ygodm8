#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"
#include "the_forceful_sentry.h"

void UpdateAllDuelGfx(void);

u8 CanActivateTheForcefulSentry(void)
{
  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

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

static void ReturnHandCardToDeck(u8 duelist, u8 handZone)
{
  struct DuelCard *handCard = gTurnHands[duelist][handZone];
  u16 cardId = handCard->id;
  u8 deckSize;

  if (cardId == CARD_NONE)
    return;

  deckSize = NumCardsInDeck(duelist);
  ClearZone(handCard);

  if (gDuelDecks[duelist].cardsDrawn > 0)
    gDuelDecks[duelist].cardsDrawn--;

  gDuelDecks[duelist].cards[gDuelDecks[duelist].cardsDrawn] = cardId;
  ShuffleDeckRange(duelist, gDuelDecks[duelist].cardsDrawn, deckSize);
}

static u8 PickRandomOpponentHandZone(void)
{
  u8 i;
  u8 occupied = Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i]->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void ResolveForActivePlayer(void)
{
  s8 chosenZone;

  chosenZone = SelectExchangeHandCard(gTurnHands[INACTIVE_DUELIST]);

  if (chosenZone < 0)
    return;

  ReturnHandCardToDeck(INACTIVE_DUELIST, (u8)chosenZone);
}

static void ResolveForInactivePlayer(void)
{
  u8 chosenZone;

  chosenZone = PickRandomOpponentHandZone();
  if (chosenZone == 0xFF)
    return;

  ReturnHandCardToDeck(INACTIVE_DUELIST, chosenZone);
}

APPEND_TEXT void EffectTheForcefulSentry(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (!CanActivateTheForcefulSentry())
    return;

  Duel_ShowEffectText(THE_FORCEFUL_SENTRY);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    ResolveForActivePlayer();
  else
    ResolveForInactivePlayer();

  UpdateAllDuelGfx();
}
