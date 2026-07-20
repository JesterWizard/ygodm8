#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_PRIESTESS(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_PRIESTESS)
    return FALSE;

  /* ponytail: Necrovalley field treatment + GK ATK/DEF boost need continuous hooks.
   * Ceiling: not ignition-activatable here; upgrade: permanent/field overlay. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_PRIESTESSEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_PRIESTESS, 2);
}
