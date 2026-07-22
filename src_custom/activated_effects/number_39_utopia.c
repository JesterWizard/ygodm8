#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateNUMBER_39_UTOPIA(void)
{
  if (gMonEffect.id != NUMBER_39_UTOPIA)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateNUMBER_39_UTOPIAEffect(void)
{
  Duel_ShowEffectTextTyped(NUMBER_39_UTOPIA, 2);
}
