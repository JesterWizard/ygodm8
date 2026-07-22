#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGAGAGIGO_THE_RISEN(void)
{
  if (gMonEffect.id != GAGAGIGO_THE_RISEN)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateGAGAGIGO_THE_RISENEffect(void)
{
  /* Printed remainder omitted by this ruleset. */
  Duel_ShowEffectTextTyped(GAGAGIGO_THE_RISEN, 2);
}
