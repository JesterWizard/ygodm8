#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMIRROR_FORCE_DRAGON(void)
{
  if (gMonEffect.id != MIRROR_FORCE_DRAGON)
    return FALSE;

  /* when targeted for attack/effect trigger needs protection hook.
   * Ceiling: not ignition-activatable here; upgrade: trigger destroy-all. */
  return FALSE;
}

void ActivateMIRROR_FORCE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(MIRROR_FORCE_DRAGON, 2);
}
