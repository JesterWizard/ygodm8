#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void)
{
  /* ponytail: control lock + End Phase LV6 SS need continuous/battle-end hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void)
{
}
