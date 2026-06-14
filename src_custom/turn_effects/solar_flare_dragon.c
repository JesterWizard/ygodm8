#include "global.h"
#include "common-chax.h"

#define SOLAR_FLARE_DRAGON_DAMAGE 500

unsigned char ShouldActivateSolarFlareDragonTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != SOLAR_FLARE_DRAGON)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateSolarFlareDragonTurnEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(SOLAR_FLARE_DRAGON_DAMAGE);
  else
    SetPlayerLifePointsToSubtract(SOLAR_FLARE_DRAGON_DAMAGE);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = SOLAR_FLARE_DRAGON;
    ActivateCardEffectText();
  }
}
