#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_ALEXANDER(void)
{
  /* ponytail: spell immunity + GB tag-out need continuous/battle-end hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_ALEXANDER(void)
{
}
