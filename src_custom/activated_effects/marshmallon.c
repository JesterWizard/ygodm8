#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateMARSHMALLON(void)
{
  if (gMonEffect.id != MARSHMALLON)
    return FALSE;

  /* ponytail: battle destruction immunity + flip-attack burn need battle hooks.
   * Ceiling: not ignition-activatable here; upgrade: battle damage / destroy gate. */
  return FALSE;
}

void ActivateMARSHMALLONEffect(void)
{
  Duel_ShowEffectTextTyped(MARSHMALLON, 2);
}
