#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "the_calculator.h"

#define THE_CALCULATOR_ATK_PER_LEVEL 300

static u8 SumFaceUpLevelsOnFixedRow(u8 fixedRow)
{
  u8 col;
  u8 total = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || !zone->isFaceUp || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    SetCardInfo(zone->id);
    total += gCardInfo.level;
  }
  return total;
}

u8 TheCalculator_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u16 atk;

  if (zone == NULL || zone->id != THE_CALCULATOR)
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  atk = Duel_StatFromCount(SumFaceUpLevelsOnFixedRow(fixedRow), THE_CALCULATOR_ATK_PER_LEVEL, 0);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateTHE_CALCULATOR(void)
{
  if (gMonEffect.id != THE_CALCULATOR)
    return FALSE;

  /* Continuous ATK via TheCalculator_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateTHE_CALCULATOREffect(void)
{
  Duel_ShowEffectTextTyped(THE_CALCULATOR, 2);
}
