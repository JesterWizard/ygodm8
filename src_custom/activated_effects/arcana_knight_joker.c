#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateARCANA_KNIGHT_JOKER(void)
{
  if (gMonEffect.id != ARCANA_KNIGHT_JOKER)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateARCANA_KNIGHT_JOKEREffect(void)
{
  Duel_ShowEffectTextTyped(ARCANA_KNIGHT_JOKER, 2);
}
