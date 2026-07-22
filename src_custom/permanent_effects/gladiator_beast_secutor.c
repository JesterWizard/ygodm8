#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_SECUTOR(void)
{
  /* Tag-out SS 2 GB via CanActivateGLADIATOR_BEAST_SECUTOR / GladiatorBeast_ActivateDeckTagOutTwo. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_SECUTOR(void)
{
}
