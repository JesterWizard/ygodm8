#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateD_D_WARRIOR(void)
{
  if (gMonEffect.id != D_D_WARRIOR)
    return FALSE;

  /* Banish both after damage calc via ApplyDDWarriorBattleEffect in battle_effects/d_d_warrior.c. */
  return FALSE;
}

void ActivateD_D_WARRIOREffect(void)
{
  Duel_ShowEffectTextTyped(D_D_WARRIOR, 2);
}
