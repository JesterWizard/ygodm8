#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateDRAGON_MASTER_MAGIA(void)
{
  /* ponytail: Quick negate-by-card-type needs chain/OPT hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDRAGON_MASTER_MAGIA(void)
{
}
