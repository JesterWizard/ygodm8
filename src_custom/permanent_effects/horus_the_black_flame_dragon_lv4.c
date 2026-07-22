#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void)
{
  /* Control lock needs continuous hook. EP send self → SS LV6 via
   * TryApplyHorusEndPhase when this card destroyed a monster by battle. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void)
{
}
