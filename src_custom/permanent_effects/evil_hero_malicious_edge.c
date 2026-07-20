#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_MALICIOUS_EDGE(void)
{
  /* ponytail: piercing + 1-tribute summon gate need battle/summon hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_MALICIOUS_EDGE(void)
{
}
