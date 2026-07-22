#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateFLAME_RULER(void)
{
  if (gMonEffect.id != FLAME_RULER)
    return FALSE;

  /* Treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump
   * outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateFLAME_RULEREffect(void)
{
  Duel_ShowEffectTextTyped(FLAME_RULER, 2);
}
