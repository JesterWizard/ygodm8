#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMAGICAL_PLANT_MANDRAGOLA(void)
{
  if (gMonEffect.id != MAGICAL_PLANT_MANDRAGOLA)
    return FALSE;

  /* FLIP place Spell Counters needs flip + counter storage outside this file.
   * Not field-ignition. */
  return FALSE;
}

void ActivateMAGICAL_PLANT_MANDRAGOLAEffect(void)
{
  Duel_ShowEffectTextTyped(MAGICAL_PLANT_MANDRAGOLA, 2);
}
