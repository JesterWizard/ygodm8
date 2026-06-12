#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

#define RAIN_OF_MERCY_LP 1000

APPEND_TEXT void EffectRainOfMercy(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    SetPlayerLifePointsToAdd(RAIN_OF_MERCY_LP);
    HandleAtkAndLifePointsAction();

    SetOpponentLifePointsToAdd(RAIN_OF_MERCY_LP);
    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = RAIN_OF_MERCY;
      ActivateCardEffectText();
    }
  } else {
    ActivateTrapEffect(RAIN_OF_MERCY_LP);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
