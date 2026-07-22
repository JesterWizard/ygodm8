#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
  /* ponytail: battle DEF burn needs battle-end/destroy hook; tag-out via CanActivateGLADIATOR_BEAST_GAIODIAZ. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
}
