#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateCureMermaidTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(CURE_MERMAID, FALSE, FALSE);
}

void ActivateCureMermaidTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), 800, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(CURE_MERMAID, 9);
}
