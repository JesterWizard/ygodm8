#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateWhiteMagicianPikeruTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != WHITE_MAGICIAN_PIKERU)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateWhiteMagicianPikeruTurnEffect(void)
{
  u16 lifePoints = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) * 400;

  if (Duel_ChangeLp(WhoseTurn(), lifePoints, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(WHITE_MAGICIAN_PIKERU, 9);
}
