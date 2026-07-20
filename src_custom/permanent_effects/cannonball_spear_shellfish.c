#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateCANNONBALL_SPEAR_SHELLFISH(void)
{
  /* ponytail: spell-immunity while Umi is face-up needs Duel_IsCardActivationBlocked
   * / targeting gate for this zone; no self-activation hook exists. */
  return FALSE;
}

void ActivateCANNONBALL_SPEAR_SHELLFISH(void)
{
}
