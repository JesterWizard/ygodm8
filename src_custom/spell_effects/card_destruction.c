#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

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
  }
}

APPEND_TEXT void EffectCardDestruction(void)
{
  u8 i;
  u8 activeCount = CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);
  u8 inactiveCount = CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    ClearZoneAndSendMonToGraveyard(gTurnHands[ACTIVE_DUELIST][i], ACTIVE_DUELIST);
    ClearZoneAndSendMonToGraveyard(gTurnHands[INACTIVE_DUELIST][i], INACTIVE_DUELIST);
  }

  DrawCards(ACTIVE_DUELIST, activeCount);
  DrawCards(INACTIVE_DUELIST, inactiveCount);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CARD_DESTRUCTION;
    ActivateCardEffectText();
  }
}
