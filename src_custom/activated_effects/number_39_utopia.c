#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateNUMBER_39_UTOPIA(void)
{
  if (gMonEffect.id != NUMBER_39_UTOPIA)
    return FALSE;

  /* Attack negate via detach + no-material self-destroy need battle hook and
   * XYZ material system outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateNUMBER_39_UTOPIAEffect(void)
{
  Duel_ShowEffectTextTyped(NUMBER_39_UTOPIA, 2);
}
