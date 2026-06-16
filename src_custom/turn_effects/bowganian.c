#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateBowganianTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != BOWGANIAN)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateBowganianTurnEffect(void)
{
  if (Duel_ChangeLp(1 - WhoseTurn(), -600, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(BOWGANIAN, 9);
}
