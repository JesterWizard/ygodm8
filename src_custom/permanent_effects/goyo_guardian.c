#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGOYO_GUARDIAN(void)
{
  /* ponytail: battle-destroy SS to your DEF needs battle-end hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGOYO_GUARDIAN(void)
{
}
