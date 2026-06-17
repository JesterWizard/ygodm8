#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateMysteriousPuppeteerTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != MYSTERIOUS_PUPPETEER)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateMysteriousPuppeteerTurnEffect(void)
{
  u16 lifePoints = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) * 500;

  if (Duel_ChangeLp(WhoseTurn(), lifePoints, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(MYSTERIOUS_PUPPETEER, 9);
}
