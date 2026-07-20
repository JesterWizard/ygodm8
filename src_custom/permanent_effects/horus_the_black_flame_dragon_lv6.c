#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void)
{
  /* ponytail: spell immunity + End Phase LV8 SS need continuous/battle-end hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void)
{
}
