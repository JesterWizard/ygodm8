#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateJENIS_LIGHTSWORN_MENDER(void)
{
  /* ponytail: End Phase heal/burn after LS mill needs turn_effect hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateJENIS_LIGHTSWORN_MENDER(void)
{
}
