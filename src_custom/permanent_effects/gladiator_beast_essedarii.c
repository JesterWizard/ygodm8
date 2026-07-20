#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_ESSEDARII(void)
{
  /* ponytail: Contact Fusion has no permanent ignition path. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_ESSEDARII(void)
{
}
