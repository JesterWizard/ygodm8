#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "negate_attack.h"

void LockMonsterCardsInRow(unsigned char turnRow);

APPEND_TEXT void EffectNegateAttack(void)
{
  LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);

  Duel_DestroyZone(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    Duel_ShowEffectText(NEGATE_ATTACK);
  }
}
