#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateLEGENDARY_MAJU_GARZETT(void)
{
  /* ATK = tributed originals needs hand-tribute SS stat capture; FromHand only. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateLEGENDARY_MAJU_GARZETT(void)
{
}
