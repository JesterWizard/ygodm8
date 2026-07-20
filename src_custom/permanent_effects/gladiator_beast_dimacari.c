#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_DIMACARI(void)
{
  /* ponytail: double attack + GB tag-out need battle-end/summon hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_DIMACARI(void)
{
}
