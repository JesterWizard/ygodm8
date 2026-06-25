#include "global.h"
#include "constants/card_ids.h"
#include "cyber_twin_dragon.h"
#include "the_dark_door.h"

void TryUnlockCyberTwinDragonForSecondAttack(struct DuelCard *attacker) {
  if (attacker == NULL)
    return;

  if (attacker->id != CYBER_TWIN_DRAGON)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
