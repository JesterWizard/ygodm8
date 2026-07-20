#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateT_G_HYPER_LIBRARIAN(void)
{
  if (gMonEffect.id != T_G_HYPER_LIBRARIAN)
    return FALSE;

  /* ponytail: Synchro Summon draw trigger needs synchro hook.
   * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */
  return FALSE;
}

void ActivateT_G_HYPER_LIBRARIANEffect(void)
{
  Duel_ShowEffectTextTyped(T_G_HYPER_LIBRARIAN, 2);
}
