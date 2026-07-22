#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateEVOLZAR_DOLKKA(void)
{
  if (gMonEffect.id != EVOLZAR_DOLKKA)
    return FALSE;

  /* quick Xyz detach + negate monster effect need chain/Xyz hooks.
   * Ceiling: not field-ignition here. */
  return FALSE;
}

void ActivateEVOLZAR_DOLKKAEffect(void)
{
  Duel_ShowEffectTextTyped(EVOLZAR_DOLKKA, 2);
}
