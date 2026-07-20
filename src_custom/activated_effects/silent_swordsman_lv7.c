#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateSILENT_SWORDSMAN_LV7(void)
{
  if (gMonEffect.id != SILENT_SWORDSMAN_LV7)
    return FALSE;

  /* ponytail: continuous negate all Spell effects needs field-wide spell gate.
   * Ceiling: not ignition-activatable here; upgrade: permanent spell-negate hook. */
  return FALSE;
}

void ActivateSILENT_SWORDSMAN_LV7Effect(void)
{
  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN_LV7, 2);
}
