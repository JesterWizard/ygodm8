#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

#define EBON_MAGICIAN_CURRAN_DAMAGE_PER_MONSTER 300

unsigned char ShouldActivateEbonMagicianCurranTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != EBON_MAGICIAN_CURRAN)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->isFaceUp;
}

void ActivateEbonMagicianCurranTurnEffect(void)
{
  u16 lifePoints = Duel_CountMonstersOnTurnRow(INACTIVE_DUELIST_MONSTER_ROW)
      * EBON_MAGICIAN_CURRAN_DAMAGE_PER_MONSTER;

  if (Duel_ChangeLp(1 - WhoseTurn(), -(s32)lifePoints, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(EBON_MAGICIAN_CURRAN, 9);
}
