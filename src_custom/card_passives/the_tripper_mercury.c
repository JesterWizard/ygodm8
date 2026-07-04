#include "global.h"
#include "constants/card_ids.h"
#include "the_dark_door.h"
#include "the_tripper_mercury.h"

void TryUnlockTheTripperMercuryForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL)
    return;

  if (attacker->id != THE_TRIPPER_MERCURY)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
