#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTUNINGWARE(void)
{
  if (gMonEffect.id != TUNINGWARE)
    return FALSE;

  /* ponytail: Synchro level-2 treatment + draw-on-material need synchro hooks.
   * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */
  return FALSE;
}

void ActivateTUNINGWAREEffect(void)
{
  Duel_ShowEffectTextTyped(TUNINGWARE, 2);
}
