#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateTUNINGWARE(void)
{
  if (gMonEffect.id != TUNINGWARE)
    return FALSE;

  /* Synchro level-2 treatment + draw-on-material need synchro hooks outside this file.
   * Not field-ignition. */
  return FALSE;
}

void ActivateTUNINGWAREEffect(void)
{
  Duel_ShowEffectTextTyped(TUNINGWARE, 2);
}
