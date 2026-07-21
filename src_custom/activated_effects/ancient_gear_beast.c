#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateANCIENT_GEAR_BEAST(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_BEAST)
    return FALSE;

  /* Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap.
   * ponytail: negate destroyed-in-battle monster effects need battle hook. */
  return FALSE;
}

void ActivateANCIENT_GEAR_BEASTEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_BEAST, 2);
}
