#include "global.h"
#include "common-chax.h"
#include "dark_room_of_nightmare.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

LYN_REPLACE_CHECK(EffectTremendousFire);
APPEND_TEXT void EffectTremendousFire__Replacement(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(1000);
    else
      SetPlayerLifePointsToSubtract(1000);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = TREMENDOUS_FIRE;
      ActivateCardEffectText();
    }

    ResolveDarkRoomEffect();
  } else {
    ActivateTrapEffect(1000);
  }
}
