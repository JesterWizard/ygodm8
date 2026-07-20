#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateX_SABER_AIRBELLUM(void)
{
  if (gMonEffect.id != X_SABER_AIRBELLUM)
    return FALSE;

  /* ponytail: direct-attack battle-damage trigger needs battle hook.
   * Ceiling: not ignition-activatable here; upgrade: battle end discard. */
  return FALSE;
}

void ActivateX_SABER_AIRBELLUMEffect(void)
{
  Duel_ShowEffectTextTyped(X_SABER_AIRBELLUM, 2);
}
