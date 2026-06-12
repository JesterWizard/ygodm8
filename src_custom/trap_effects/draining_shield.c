#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "draining_shield.h"

void SaveDrainingShieldAttackResume(void);

APPEND_TEXT void EffectDrainingShield(void)
{
  u16 atk;

  SaveDrainingShieldAttackResume();

  gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;

  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToAdd(atk);
  else
    SetPlayerLifePointsToAdd(atk);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  ClearZoneAndSendMonToGraveyard(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = DRAINING_SHIELD;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}
