#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_TORAX(void)
{
  /* ponytail: GB tag-out draw after battle needs battle-end hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_TORAX(void)
{
}
