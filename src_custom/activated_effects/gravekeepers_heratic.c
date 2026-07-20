#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_HERATIC(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_HERATIC)
    return FALSE;

  /* ponytail: continuous unaffected-while-Necrovalley needs permanent protection
   * gate. Ceiling: not ignition-activatable here; upgrade: permanent effect
   * while Duel_IsBackrowCardOnField(NECROVALLEY). */
  return FALSE;
}

void ActivateGRAVEKEEPERS_HERATICEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_HERATIC, 2);
}
