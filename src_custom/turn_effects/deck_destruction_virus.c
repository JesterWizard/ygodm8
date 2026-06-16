#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateDeckDestructionVirusEffect(void)
{
  FlipCardFaceUp(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);
  Duel_MillTopDeckCards(INACTIVE_DUELIST, 5, TRUE);
  Duel_ShowEffectTextTyped(DECK_DESTRUCTION_VIRUS, 9);
}
