#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_TORAX(void)
{
  /* Tag-out draw via CanActivateGLADIATOR_BEAST_TORAX. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_TORAX(void)
{
}
