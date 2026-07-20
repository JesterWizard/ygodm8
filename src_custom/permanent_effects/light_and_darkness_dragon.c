#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateLIGHT_AND_DARKNESS_DRAGON(void)
{
  /* ponytail: chain negate (−500 ATK/DEF) + GY destroy-all/SS need chain/GY hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateLIGHT_AND_DARKNESS_DRAGON(void)
{
}
