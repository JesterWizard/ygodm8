#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_GADJILTRON_CHIMERA(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_GADJILTRON_CHIMERA)
    return FALSE;

  /* ponytail: Green/Red/Yellow Gadget tribute branches (+300 ATK, direct burn,
   * battle burn) need summon/tribute hooks. Ceiling: not ignition-activatable. */
  return FALSE;
}

void ActivateANCIENT_GEAR_GADJILTRON_CHIMERAEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GADJILTRON_CHIMERA, 2);
}
