#include "global.h"
#include "common-chax.h"

unsigned char CanActivateMysteriousPuppeteer(void)
{
  return gMonEffect.id == MYSTERIOUS_PUPPETEER;
}

static u16 CountMonstersOnSide(u8 row)
{
  u8 i;
  u16 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[row][i]->id != CARD_NONE)
      count++;

  return count;
}

void ActivateMysteriousPuppeteerEffect(void)
{
  u16 lifePoints = CountMonstersOnSide(gMonEffect.row) * 500;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToAdd(lifePoints);
  else
    SetOpponentLifePointsToAdd(lifePoints);

  HandleAtkAndLifePointsAction();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = MYSTERIOUS_PUPPETEER;
    ActivateCardEffectText();
  }
}
