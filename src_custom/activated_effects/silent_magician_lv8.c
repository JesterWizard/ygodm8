#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateSILENT_MAGICIAN_LV8(void)
{
  if (gMonEffect.id != SILENT_MAGICIAN_LV8)
    return FALSE;

  /* ponytail: continuous immunity to opponent Spell effects needs spell-target gate.
   * Ceiling: not ignition-activatable here; upgrade: permanent spell-immune hook. */
  return FALSE;
}

void ActivateSILENT_MAGICIAN_LV8Effect(void)
{
  Duel_ShowEffectTextTyped(SILENT_MAGICIAN_LV8, 2);
}
