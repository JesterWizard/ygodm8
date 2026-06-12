#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

APPEND_TEXT void EffectMagicCylinder(void)
{
  u16 atk;

  gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(atk);
  else
    SetOpponentLifePointsToSubtract(atk);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  ClearZoneAndSendMonToGraveyard(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MAGIC_CYLINDER;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}
