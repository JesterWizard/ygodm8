#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_WILD_CYCLONE(void)
{
  /* ponytail: attack S/T lock + battle-damage destroy face-down S/T need battle/chain hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_WILD_CYCLONE(void)
{
}
