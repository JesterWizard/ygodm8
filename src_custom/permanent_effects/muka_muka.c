#include "global.h"

static unsigned char CountCardsInHand(struct DuelCard **hand) {
  unsigned char i;
  unsigned char count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (hand[i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static unsigned char CountMukaMukaStages(void) {
  unsigned char handCards;

  if (gActiveEffect.turnRow == 1)
    handCards = CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);
  else if (gActiveEffect.turnRow == 2)
    handCards = CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);
  else
    return 0;

  return handCards / 2;
}

unsigned char ShouldActivateMukaMuka(void) {
  if (gActiveEffect.turnRow != 1 && gActiveEffect.turnRow != 2)
    return FALSE;

  return gActiveEffect.cardId == MUKA_MUKA;
}

void ActivateMukaMuka(void) {
  unsigned char stages;

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  FlipCardFaceUp(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);

  stages = CountMukaMukaStages();
  while (stages--)
    IncrementTempStage(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MUKA_MUKA;
    ActivateCardEffectText();
  }
}
