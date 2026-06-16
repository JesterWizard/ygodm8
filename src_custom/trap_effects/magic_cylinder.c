#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

APPEND_TEXT void EffectMagicCylinder(void)
{
  u16 atk;

  gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;

  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)atk, FALSE);
  Duel_DestroyZone(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    Duel_ShowEffectText(MAGIC_CYLINDER);
  }
}
