#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMORPHTRONIC_LANTRON(void)
{
  if (gMonEffect.id != MORPHTRONIC_LANTRON)
    return FALSE;

  /* ponytail: ATK redirect effect damage + DEF no battle damage when destroyed
   * need damage-redirect and battle-destroy hooks. Ceiling: not ignition here. */
  return FALSE;
}

void ActivateMORPHTRONIC_LANTRONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_LANTRON, 2);
}
