#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_SAMNITE(void)
{
  /* ponytail: battle search needs battle-end/destroy hook; tag-out via CanActivateGLADIATOR_BEAST_SAMNITE. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_SAMNITE(void)
{
}
