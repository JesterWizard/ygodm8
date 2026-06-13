#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define GRACEFUL_CHARITY_DRAW_COUNT 3
#define GRACEFUL_CHARITY_DISCARD_COUNT 2

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 CountCardsInHand(struct DuelCard **hand)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (hand[i]->id != CARD_NONE)
      count++;

  return count;
}

static void DrawCards(u8 duelist, u8 count)
{
  u8 i;

  for (i = 0; i < count; i++) {
    if (gDuelDecks[duelist].cardsDrawn >= NumCardsInDeck(duelist)) {
      DeclareLoser(duelist);
      return;
    }

    TryDrawingCard(duelist);

    if (IsDuelOver() == TRUE)
      return;
  }
}

static s8 PickRandomHandZone(struct DuelCard **handRow)
{
  u8 i;
  u8 occupied = CountCardsInHand(handRow);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return -1;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return -1;
}

static void DiscardSelectedCards(void)
{
  u8 i;
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  for (i = 0; i < GRACEFUL_CHARITY_DISCARD_COUNT; i++) {
    s8 zone;

    if (CountCardsInHand(handRow) == 0)
      break;

    if (WhoseTurn() == DUEL_PLAYER)
      zone = SelectHandCardMatchingPredicate(handRow, AnyHandCard);
    else
      zone = PickRandomHandZone(handRow);

    if (zone < 0)
      break;

    ClearZoneAndSendMonToGraveyard(handRow[zone], ACTIVE_DUELIST);
  }
}

APPEND_TEXT void EffectGracefulCharity(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = GRACEFUL_CHARITY;
    ActivateCardEffectText();
  }

  if (IsDuelOver() != TRUE) {
    DrawCards(ACTIVE_DUELIST, GRACEFUL_CHARITY_DRAW_COUNT);
    UpdateDuelGfxExceptField();

    if (IsDuelOver() != TRUE)
      DiscardSelectedCards();
  }

  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  UpdateDuelGfxExceptField();
}
