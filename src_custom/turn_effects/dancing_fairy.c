#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define DANCING_FAIRY_STANDBY_HEAL 1000

unsigned char ShouldActivateDancingFairyTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != DANCING_FAIRY)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp == TRUE && zone->isDefending == TRUE;
}

void ActivateDancingFairyTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), DANCING_FAIRY_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(DANCING_FAIRY);
}
