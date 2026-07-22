#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTIME_MAGIC_HAMMER(void)
{
  if (gMonEffect.id != TIME_MAGIC_HAMMER)
    return FALSE;

  /* Hermos equip + battle-step dice banish need summon/equip/battle hooks
   * outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateTIME_MAGIC_HAMMEREffect(void)
{
  Duel_ShowEffectTextTyped(TIME_MAGIC_HAMMER, 2);
}
