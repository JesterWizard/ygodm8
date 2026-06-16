#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void ActivateGoddessOfWhimEffect(void)
{
  u8 turn = WhoseTurn();

  if (Duel_ChangeLp(turn, -500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DrawCards(turn, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(GODDESS_OF_WHIM, 2);
}
