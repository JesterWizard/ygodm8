#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_DIMACARI(void)
{
  /* ponytail: double attack needs battle-end/summon hook; tag-out via CanActivateGLADIATOR_BEAST_DIMACARI. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_DIMACARI(void)
{
}
