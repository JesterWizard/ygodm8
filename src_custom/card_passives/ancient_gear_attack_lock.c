#include "global.h"
#include "ancient_gear_attack_lock.h"
#include "constants/card_ids.h"

u8 AncientGear_AttackerBlocksOppSpellTrap(const struct DuelCard *attacker)
{
  if (attacker == NULL)
    return FALSE;

  switch (attacker->id) {
  case ANCIENT_GEAR_GOLEM:
  case ANCIENT_GEAR_SOLDIER:
  case ANCIENT_GEAR_BEAST:
  case ANCIENT_GEAR_KNIGHT:
  case ANCIENT_GEAR_ENGINEER:
  case ANCIENT_GEAR_FRAME:
  case ANCIENT_GEAR_CANNON:
  case ANCIENT_GEAR_GADJILTRON_DRAGON:
  case ULTIMATE_ANCIENT_GEAR_GOLEM:
  case ANCIENT_GEAR_GOLEM_ULTIMATE_POUND:
    return TRUE;
  default:
    return FALSE;
  }
}
