#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateDESTINY_HERO_DREAD_SERVANT(void)
{
  /* ponytail: Clock Tower counters + battle-destroy S/T need NS/battle hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DREAD_SERVANT(void)
{
}
