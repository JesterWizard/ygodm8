#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateCANNONBALL_SPEAR_SHELLFISH(void)
{
  /* Continuous Umi spell-immunity via IsImmuneToSpellEffectsOnField — not ignition. */
  return FALSE;
}

void ActivateCANNONBALL_SPEAR_SHELLFISH(void)
{
}
