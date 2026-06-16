#include "global.h"
#include "common-chax.h"
#include "copycat.h"
#include "duel_helpers.h"

void ActivateCopycatEffect(void) {
  u8 enemyRow = (gMonEffect.row == 1) ? 2 : 1;
  struct DuelCard *copycatZone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 targetZone;
  struct StatMod targetStatMod;
  u16 copiedAtk = 0;
  u16 copiedDef = 0;

  targetZone = FindStrongestEnemyMonsterZone(gTurnZones[enemyRow]);
  if (targetZone >= 0) {
    gComputingCopycatStats = TRUE;
    targetStatMod.card = gTurnZones[enemyRow][targetZone]->id;
    targetStatMod.field = gDuel.field;
    targetStatMod.stage = GetFinalStage(gTurnZones[enemyRow][targetZone]);
    SetFinalStat(&targetStatMod);
    copiedAtk = gCardInfo.atk;
    copiedDef = gCardInfo.def;
    gComputingCopycatStats = FALSE;
  }

  StoreCopycatBoardStats(copycatZone, copiedAtk, copiedDef);
  Duel_ShowEffectTextTyped(COPYCAT, 2);
}
