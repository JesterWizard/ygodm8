#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateNATURIA_BEAST(void)
{
  if (gMonEffect.id != NATURIA_BEAST)
    return FALSE;

  /* Quick Effect spell negate + mill 2 need chain/negation hooks outside this file.
   * Not field-ignition. */
  return FALSE;
}

void ActivateNATURIA_BEASTEffect(void)
{
  Duel_ShowEffectTextTyped(NATURIA_BEAST, 2);
}
