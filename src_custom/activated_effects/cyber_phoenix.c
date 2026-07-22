#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "cyber_phoenix.h"

unsigned char CanActivateCYBER_PHOENIX(void)
{
  if (gMonEffect.id != CYBER_PHOENIX)
    return FALSE;

  /* Battle-destroy draw via ApplyCyberPhoenixBattleDestroyDraw.
   * ponytail: ATK-position Machine S/T target-negate needs targeting gate. */
  return FALSE;
}

void ActivateCYBER_PHOENIXEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
}
