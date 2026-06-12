#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

#define GOBLIN_THIEF_LP 500

APPEND_TEXT void EffectGoblinThief(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText)
  {
    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(GOBLIN_THIEF_LP);
    else
      SetPlayerLifePointsToSubtract(GOBLIN_THIEF_LP);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    if (WhoseTurn() == DUEL_PLAYER)
      SetPlayerLifePointsToAdd(GOBLIN_THIEF_LP);
    else
      SetOpponentLifePointsToAdd(GOBLIN_THIEF_LP);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    if (!gHideEffectText)
    {
      gCardEffectTextData.cardId = GOBLIN_THIEF;
      ActivateCardEffectText();
    }
  }
  else
    ActivateTrapEffect(GOBLIN_THIEF_LP);

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
