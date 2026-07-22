#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_DIMACARI(void)
{
  /* Double attack via TryMarkBuiltInExtraAttackOnPlacement; tag-out via CanActivateGLADIATOR_BEAST_DIMACARI. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_DIMACARI(void)
{
}
