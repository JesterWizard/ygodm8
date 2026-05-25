#include "global.h"
#include "common-chax.h"

static void MillDeck(u8 duelist)
{
  u8 i;

  for (i = 0; i < 5; i++)
  {
    if (gDuelDecks[duelist].cardsDrawn >= NumCardsInDeck(duelist))
      break;

    gDuelDecks[duelist].cardsDrawn++;
  }
}

void ActivateDeckDestructionVirusEffect(void)
{
  FlipCardFaceUp(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);
  MillDeck(INACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = DECK_DESTRUCTION_VIRUS;
    ActivateCardEffectText();
  }
}
