#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

#define EXCHANGE_SPIRIT_MIN_GY 15
#define EXCHANGE_SPIRIT_LP_COST 1000

static u8 sExchangeOfTheSpiritUsed APPEND_DATA = {0};

static u8 GyCount(u8 fixedDuelist)
{
  if (GraveyardExpand_IsEnabled())
    return GraveyardExpand_GetCount(fixedDuelist);

  return gDuel.duelistbattleState[fixedDuelist].graveyard != CARD_NONE ? 1 : 0;
}

static void SwapDeckAndGraveyard(u8 fixedDuelist)
{
  u16 deckBuf[60];
  u16 gyBuf[EXPANDED_GRAVEYARD_CAPACITY];
  u8 deckSize;
  u8 gyCount;
  u8 i;
  u8 top;

  if (!GraveyardExpand_IsEnabled())
    return;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  if (gyCount > EXPANDED_GRAVEYARD_CAPACITY)
    gyCount = EXPANDED_GRAVEYARD_CAPACITY;

  for (i = 0; i < gyCount; i++)
    gyBuf[i] = GraveyardExpand_GetCardAt(fixedDuelist, i);

  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;
  if (deckSize > 60)
    deckSize = 60;

  for (i = 0; i < deckSize; i++)
    deckBuf[i] = gDuelDecks[fixedDuelist].cards[i];

  /* Clear GY then push former deck (undrawn first as new GY order). */
  while (GraveyardExpand_GetCount(fixedDuelist) > 0)
    GraveyardExpand_PopFixed(fixedDuelist);

  for (i = top; i < deckSize; i++)
    GraveyardExpand_PushFixed(fixedDuelist, deckBuf[i]);
  for (i = 0; i < top && i < deckSize; i++)
    GraveyardExpand_PushFixed(fixedDuelist, deckBuf[i]);

  /* Rebuild deck from former GY. */
  for (i = 0; i < 60; i++)
    gDuelDecks[fixedDuelist].cards[i] = CARD_NONE;
  for (i = 0; i < gyCount; i++)
    gDuelDecks[fixedDuelist].cards[i] = gyBuf[i];
  gDuelDecks[fixedDuelist].cardsDrawn = 0;
  /* NumCardsInDeck may be separate — shuffle from drawn. */
  Duel_ShuffleDeckFromDrawn(fixedDuelist == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT);
}

APPEND_TEXT void EffectEXCHANGE_OF_THE_SPIRIT(void)
{
  Duel_ShowTrapResponseText(EXCHANGE_OF_THE_SPIRIT, gTrapEffectData.originCardId);

  if (sExchangeOfTheSpiritUsed
      || GyCount(DUEL_PLAYER) < EXCHANGE_SPIRIT_MIN_GY
      || GyCount(DUEL_OPPONENT) < EXCHANGE_SPIRIT_MIN_GY) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  Duel_ChangeLp(INACTIVE_DUELIST, -EXCHANGE_SPIRIT_LP_COST, FALSE);
  SwapDeckAndGraveyard(DUEL_PLAYER);
  SwapDeckAndGraveyard(DUEL_OPPONENT);
  sExchangeOfTheSpiritUsed = TRUE;

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
