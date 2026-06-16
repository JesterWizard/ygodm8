#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ARSENAL_BUG_DEBUFF_STAGES 2

static u8 CountOtherInsectMonstersOnRow(u8 turnRow, u8 exceptCol)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (i == exceptCol)
      continue;

    if (gTurnZones[turnRow][i]->id == CARD_NONE)
      continue;

    SetCardInfo(gTurnZones[turnRow][i]->id);
    if (gCardInfo.type == TYPE_INSECT)
      count++;
  }

  return count;
}

unsigned char ShouldActivateArsenalBug(void)
{
  if (gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (gActiveEffect.cardId != ARSENAL_BUG)
    return FALSE;

  return CountOtherInsectMonstersOnRow(gActiveEffect.turnRow, gActiveEffect.col) == 0;
}

void ActivateArsenalBug(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  u8 stages = ARSENAL_BUG_DEBUFF_STAGES;

  FlipCardFaceUp(zone);

  while (stages--)
    DecrementTempStage(zone);

  Duel_ShowEffectTextTyped(ARSENAL_BUG, 8);
}
