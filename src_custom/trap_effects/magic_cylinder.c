#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void LockMonsterCardsInRow(unsigned char turnRow);

APPEND_TEXT void EffectMagicCylinder(void)
{
  u16 atk;

  LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);

  gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;

  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)atk, FALSE);

  /* ponytail: Normal Trap must leave the backrow to prevent AI re-trigger loop */
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  Duel_ShowTrapResponseText(MAGIC_CYLINDER, gTrapEffectData.originCardId);
}
