#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateCureMermaidTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != CURE_MERMAID)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateCureMermaidTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), 800, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(CURE_MERMAID, 9);
}
