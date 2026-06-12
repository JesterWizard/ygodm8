#include "global.h"
#include "constants/card_ids.h"
#include "hayabusa_knight.h"

void TryUnlockHayabusaKnightForSecondAttack(struct DuelCard *attacker) {
  if (attacker == NULL)
    return;

  if (attacker->id != HAYABUSA_KNIGHT)
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
