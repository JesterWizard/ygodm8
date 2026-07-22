#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGREAT_POSEIDON_BEETLE(void)
{
  if (gMonEffect.id != GREAT_POSEIDON_BEETLE)
    return FALSE;

  /* re-attack same target after surviving battle needs battle
   * re-attack hook. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateGREAT_POSEIDON_BEETLEEffect(void)
{
  Duel_ShowEffectTextTyped(GREAT_POSEIDON_BEETLE, 2);
}
