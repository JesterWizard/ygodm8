#include "global.h"
#include "common-chax.h"
#include "delayed_effects.h"
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

APPEND_TEXT void EffectCardOfDemise(void)
{
  u8 turn = WhoseTurn();

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  while (CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 5)
  {
    if (gDuelDecks[ACTIVE_DUELIST].cardsDrawn >= NumCardsInDeck(ACTIVE_DUELIST))
    {
      DeclareLoser(ACTIVE_DUELIST);
      break;
    }

    TryDrawingCard(ACTIVE_DUELIST);
  }

  QueueDelayedDuelEffect(turn, DELAYED_DUEL_EFFECT_CARD_OF_DEMISE);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = CARD_OF_DEMISE;
    ActivateCardEffectText();
  }
}
