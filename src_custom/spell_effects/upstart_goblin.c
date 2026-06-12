#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

#define UPSTART_GOBLIN_LP 1000

APPEND_TEXT void EffectUpstartGoblin(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    TryDrawingCard(ACTIVE_DUELIST);

    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToAdd(UPSTART_GOBLIN_LP);
    else
      SetPlayerLifePointsToAdd(UPSTART_GOBLIN_LP);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = UPSTART_GOBLIN;
      ActivateCardEffectText();
    }
  } else {
    ActivateTrapEffect(UPSTART_GOBLIN_LP);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
