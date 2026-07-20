#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
  /* ponytail: double attack + destroyed Standby 2 Tokens need battle/turn hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
}
