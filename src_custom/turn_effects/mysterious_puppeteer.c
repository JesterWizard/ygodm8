#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateMysteriousPuppeteerTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(MYSTERIOUS_PUPPETEER, FALSE, FALSE);
}

void ActivateMysteriousPuppeteerTurnEffect(void)
{
  u16 lifePoints = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) * 500;

  if (Duel_ChangeLp(WhoseTurn(), lifePoints, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(MYSTERIOUS_PUPPETEER, 9);
}
