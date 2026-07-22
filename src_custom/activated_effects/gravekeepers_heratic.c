#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_HERATIC(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_HERATIC)
    return FALSE;

  /* Unaffected while Necrovalley face-up via IsImmuneToHarmfulTargetedEffectsOnField. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_HERATICEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_HERATIC, 2);
}
