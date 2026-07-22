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
   * Negate destroyed-in-battle monster effects via ApplyHarpieLady2FlipNegation. */
  return FALSE;
}

void ActivateANCIENT_GEAR_BEASTEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_BEAST, 2);
}
