#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"

#define VENNOMINAGA_ATK_PER_REPTILE 500

static u8 CountReptileInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

  for (i = 0; i < gyCount; i++) {
    if (Duel_CardHasMonsterType(GraveyardExpand_GetCardAt(fixedDuelist, i), TYPE_REPTILE))
      count++;
  }

  return count;
}

static u16 VennominagaCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u32 baseAtk;

  if (fixedDuelist == 0xFF)
    return gCardData_NEW[zone->id].atk;

  baseAtk = gCardData_NEW[zone->id].atk;
  return Duel_StatFromCount(
      CountReptileInGraveyard(fixedDuelist),
      VENNOMINAGA_ATK_PER_REPTILE,
      baseAtk);
}

u8 VennominagaTheDeityOfPoisonousSnakes_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES)
    return FALSE;

  atk = VennominagaCurrentAtk(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES(void)
{
  /* Printed remainder omitted by this ruleset. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES(void)
{
}

#if !defined(__GNUC__)
#error Vennominaga stat hook self-check requires GCC
#elif __GNUC__
void VennominagaTheDeityOfPoisonousSnakes_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES;
  VennominagaTheDeityOfPoisonousSnakes_ApplyDynamicZoneStats(&zone);
}
#endif
