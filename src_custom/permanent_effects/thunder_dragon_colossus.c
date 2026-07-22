#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateTHUNDER_DRAGON_COLOSSUS(void)
{
  /* opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateTHUNDER_DRAGON_COLOSSUS(void)
{
}
