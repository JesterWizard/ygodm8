#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateENRAGED_BATTLE_OX(void)
{
  if (gMonEffect.id != ENRAGED_BATTLE_OX)
    return FALSE;

  /* ponytail: piercing battle damage needs battle damage gate.
   * Ceiling: not ignition-activatable here; upgrade: permanent/battle overlay. */
  return FALSE;
}

void ActivateENRAGED_BATTLE_OXEffect(void)
{
  Duel_ShowEffectTextTyped(ENRAGED_BATTLE_OX, 2);
}
