#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateREPTILIANNE_NAGA(void)
{
  /* ponytail: battle immunity, ATK-to-0, and EP flip need battle/turn hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateREPTILIANNE_NAGA(void)
{
}
