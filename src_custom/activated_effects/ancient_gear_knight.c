#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_KNIGHT(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_KNIGHT)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateANCIENT_GEAR_KNIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_KNIGHT, 2);
}
