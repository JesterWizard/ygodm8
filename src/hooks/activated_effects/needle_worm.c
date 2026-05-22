#include "global.h"
#include "common-chax.h"

void ActivateNeedleWormEffect(void)
{
  u8 i;
  u8 opponent = 1 - WhoseTurn();

  for (i = 0; i < 5; i++)
  {
    if (gDuelDecks[opponent].cardsDrawn >= NumCardsInDeck(opponent))
      break;

    gDuelDecks[opponent].cardsDrawn++;
  }

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = NEEDLE_WORM;
    ActivateCardEffectText();
  }
}
