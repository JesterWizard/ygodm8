#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char CanActivateENRAGED_BATTLE_OX(void)
{
  if (gMonEffect.id != ENRAGED_BATTLE_OX)
    return FALSE;

  /* Pierce via ApplySimplePiercersBattleEffect. */
  return FALSE;
}

void ActivateENRAGED_BATTLE_OXEffect(void)
{
  Duel_ShowEffectTextTyped(ENRAGED_BATTLE_OX, 2);
}
