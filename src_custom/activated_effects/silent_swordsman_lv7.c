#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char CanActivateSILENT_SWORDSMAN_LV7(void)
{
  if (gMonEffect.id != SILENT_SWORDSMAN_LV7)
    return FALSE;

  /* Spell immunity via IsImmuneToSpellEffectsOnField; not ignition-activatable. */
  return FALSE;
}

void ActivateSILENT_SWORDSMAN_LV7Effect(void)
{
  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN_LV7, 2);
}
