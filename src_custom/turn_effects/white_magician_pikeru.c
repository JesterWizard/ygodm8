#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char ShouldActivateWhiteMagicianPikeruTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(WHITE_MAGICIAN_PIKERU, FALSE, FALSE);
}

void ActivateWhiteMagicianPikeruTurnEffect(void)
{
  u16 lifePoints = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) * 400;

  if (Duel_ChangeLp(WhoseTurn(), lifePoints, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(WHITE_MAGICIAN_PIKERU, 9);
}
