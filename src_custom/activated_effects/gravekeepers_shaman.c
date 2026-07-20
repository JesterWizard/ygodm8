#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_SHAMAN(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_SHAMAN)
    return FALSE;

  /* ponytail: DEF per GK in GY + GY effect negate + Necrovalley Field Spell lock
   * need permanent hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_SHAMANEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SHAMAN, 2);
}
