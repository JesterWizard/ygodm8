#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_SECUTOR(void)
{
  /* ponytail: battle-end tag SS 2 GB from Deck needs battle-end hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_SECUTOR(void)
{
}
