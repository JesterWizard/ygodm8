#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 ControlsOnlyThisMonster(u8 turnRow, u8 col)
{
  u8 c;
  u8 count = 0;

  for (c = 0; c < MAX_ZONES_IN_ROW; c++) {
    if (gTurnZones[turnRow][c]->id == CARD_NONE)
      continue;

    count++;
    if (count > 1)
      return FALSE;
  }

  return count == 1 && gTurnZones[turnRow][col]->id == YOWIE;
}

unsigned char ShouldActivateYOWIE(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != YOWIE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return ControlsOnlyThisMonster(gActiveEffect.turnRow, gActiveEffect.col);
}

void ActivateYOWIE(void)
{
  struct DuelCard *zone;

  Duel_ShowEffectTextTyped(YOWIE, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
  /* ponytail: opp skip Draw Phase needs turn hook; unk4 marks alone-summon only. */
}
