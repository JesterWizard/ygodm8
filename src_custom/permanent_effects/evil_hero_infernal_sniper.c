#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_INFERNAL_SNIPER(void)
{
  /* ponytail: spell immunity + Standby burn 1000 (face-up DEF) need continuous/phase hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNAL_SNIPER(void)
{
}
