#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

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
  if (Duel_ChangeLp(1 - WhoseTurn(), -SOLAR_FLARE_DRAGON_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(SOLAR_FLARE_DRAGON, 9);
}
