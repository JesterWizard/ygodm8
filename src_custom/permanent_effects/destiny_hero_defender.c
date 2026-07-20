#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateDESTINY_HERO_DEFENDER(void)
{
  /* ponytail: opp Standby draw while face-up DEF needs turn_effect hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DEFENDER(void)
{
}
