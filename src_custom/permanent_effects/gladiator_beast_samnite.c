#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_SAMNITE(void)
{
  /* ponytail: battle search + GB tag-out need battle-end/destroy hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_SAMNITE(void)
{
}
