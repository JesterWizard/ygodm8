#include "global.h"
#include "common-chax.h"

static u16 CountMonstersOnSide(u8 row)
{
  u8 i;
  u16 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[row][i]->id != CARD_NONE)
      count++;

  return count;
}

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
  u16 lifePoints = CountMonstersOnSide(ACTIVE_DUELIST_MONSTER_ROW) * 500;

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
