#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
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

  Duel_ChangeLp(INACTIVE_DUELIST, atk, FALSE);
  Duel_DestroyZone(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  Duel_ShowTrapResponseText(DRAINING_SHIELD, gTrapEffectData.originCardId);
}
