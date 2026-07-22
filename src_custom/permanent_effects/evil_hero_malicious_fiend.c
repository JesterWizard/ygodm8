#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_MALICIOUS_FIEND(void)
{
  /* Pierce via ApplySimplePiercersBattleEffect.
   * ponytail: forced attack + face-up Attack Position need battle redirect hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_MALICIOUS_FIEND(void)
{
}
