#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateEVIL_HERO_INFERNAL_PRODIGY(void)
{
  /* ponytail: empty-field hand SS is FromHand activated; End-Phase tribute draw needs turn hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNAL_PRODIGY(void)
{
}
