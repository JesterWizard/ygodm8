#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void)
{
  /* Spell immunity via IsImmuneToSpellEffectsOnField. EP send self → SS LV8
   * via TryApplyHorusEndPhase when this card destroyed a monster by battle. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void)
{
}
