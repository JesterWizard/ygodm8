#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "negate_attack.h"

void LockMonsterCardsInRow(unsigned char turnRow);

APPEND_TEXT void EffectNegateAttack(void)
{
  LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);

  ClearZoneAndSendMonToGraveyard(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = NEGATE_ATTACK;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}
