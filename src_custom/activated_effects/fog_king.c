#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateFOG_KING(void)
{
  if (gMonEffect.id != FOG_KING)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateFOG_KINGEffect(void)
{
  Duel_ShowEffectTextTyped(FOG_KING, 2);
}
