#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

static u8 CanAddBlueEyesFromDeck(u8 turnDuelist)
{
  if (Duel_FindDeckCardIndex(turnDuelist, BLUE_EYES_WHITE_DRAGON) < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

unsigned char ShouldActivateTHE_WHITE_STONE_OF_LEGEND(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (gActiveEffect.cardId != THE_WHITE_STONE_OF_LEGEND)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != THE_WHITE_STONE_OF_LEGEND)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != THE_WHITE_STONE_OF_LEGEND)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  return CanAddBlueEyesFromDeck(turnDuelist);
}

void ActivateTHE_WHITE_STONE_OF_LEGEND(void)
{
  u8 turnDuelist;
  u8 hideEffectText;

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowEffectTextTyped(THE_WHITE_STONE_OF_LEGEND, 8);
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave(turnDuelist);
  if (CanAddBlueEyesFromDeck(turnDuelist))
    Duel_AddDeckCardToHand(turnDuelist, BLUE_EYES_WHITE_DRAGON, TRUE);
}
