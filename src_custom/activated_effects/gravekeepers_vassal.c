#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_VASSAL(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_VASSAL)
    return FALSE;

  /* The damage-class conversion is not represented by the current damage model. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_VASSALEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_VASSAL, 2);
}
