#include "global.h"
#include "dynamic_equip.h"
#include "constants/card_ids.h"
#include "the_dark_door.h"
#include "twin_swords_of_flashing_light_tryce.h"

void TryUnlockTryceEquipForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL)
    return;

  if (!DynamicEquipTargetsMonsterWithSpell(attacker, TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE))
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
