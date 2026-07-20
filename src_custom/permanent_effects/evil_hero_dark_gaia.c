#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_DARK_GAIA(void)
{
  /* ponytail: ATK = fusion materials + flip opp Defense→Attack need fusion/battle hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_DARK_GAIA(void)
{
}
