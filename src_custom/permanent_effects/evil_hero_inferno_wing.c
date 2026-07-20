#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_INFERNO_WING(void)
{
  /* ponytail: piercing + battle-destroy burn need Damage Step / battle hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNO_WING(void)
{
}
