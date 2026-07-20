#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
  /* ponytail: battle DEF burn + GB tag-out need battle-end/destroy hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
}
