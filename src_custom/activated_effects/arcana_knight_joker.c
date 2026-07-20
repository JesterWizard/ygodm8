#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARCANA_KNIGHT_JOKER(void)
{
  if (gMonEffect.id != ARCANA_KNIGHT_JOKER)
    return FALSE;

  /* ponytail: discard matching type to negate activation needs chain/response
   * hooks. Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateARCANA_KNIGHT_JOKEREffect(void)
{
  Duel_ShowEffectTextTyped(ARCANA_KNIGHT_JOKER, 2);
}
