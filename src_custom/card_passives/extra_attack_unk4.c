#include "global.h"
#include "extra_attack_unk4.h"
#include "the_dark_door.h"

void TryUnlockUnk4MarkedExtraAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->unk4 < 2)
    return;
  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
