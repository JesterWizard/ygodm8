#include "global.h"
#include "constants/card_ids.h"
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

void TryMarkBuiltInExtraAttackOnPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (zone->id == GLADIATOR_BEAST_DIMACARI || zone->id == ARMITYLE_THE_CHAOS_PHANTASM
      || zone->id == CHAOS_ANCIENT_GEAR_GIANT
      || zone->id == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND)
    zone->unk4 = 2;
}
