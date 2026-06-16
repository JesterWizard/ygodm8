#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define SPIRIT_OF_THE_BREEZE_STANDBY_HEAL 1000

unsigned char ShouldActivateSpiritOfTheBreezeTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != SPIRIT_OF_THE_BREEZE)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp == TRUE && zone->isDefending == FALSE;
}

void ActivateSpiritOfTheBreezeTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), SPIRIT_OF_THE_BREEZE_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(SPIRIT_OF_THE_BREEZE, 9);
}
