#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivateCyberStein(void)
{
  if (gMonEffect.id != CYBER_STEIN)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 5000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 5000;
}

void __attribute__((section(".append_text"))) EffectCyberStein(void)
{
  struct DuelSummonOpts opts;

  if (Duel_ChangeLp(WhoseTurn(), -5000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.markSpecialSummon = FALSE;
  opts.lockMonster = TRUE;
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, BLUE_EYES_ULTIMATE_DRAGON, opts);
  Duel_ShowEffectTextTyped(CYBER_STEIN, 2);
}
