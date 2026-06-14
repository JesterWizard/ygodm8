#include "global.h"
#include "constants/card_ids.h"
#include "hayabusa_knight.h"
#include "the_dark_door.h"

void TryUnlockHayabusaKnightForSecondAttack(struct DuelCard *attacker) {
  if (attacker == NULL)
    return;

  if (attacker->id != HAYABUSA_KNIGHT && attacker->id != MATAZA_THE_ZAPPER)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
