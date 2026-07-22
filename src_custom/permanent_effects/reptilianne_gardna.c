#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateREPTILIANNE_GARDNA(void)
{
  /* destroyed→search Reptilianne needs destroy-to-GY permanent hook. */
  return FALSE;
}

void ActivateREPTILIANNE_GARDNA(void)
{
}
