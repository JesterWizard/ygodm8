#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"

#define VENNOMINON_ATK_PER_REPTILE 500

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

static u16 VennominonCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u32 baseAtk;

  if (fixedDuelist == 0xFF)
    return gCardData_NEW[zone->id].atk;

  baseAtk = gCardData_NEW[zone->id].atk;
  return Duel_StatFromCount(
      CountReptileInGraveyard(fixedDuelist),
      VENNOMINON_ATK_PER_REPTILE,
      baseAtk);
}

u8 VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != VENNOMINON_THE_KING_OF_POISONOUS_SNAKES)
    return FALSE;

  atk = VennominonCurrentAtk(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void)
{
  /* ponytail: battle destroy → banish Reptile + SS self needs battle/GY hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void)
{
}

#if !defined(__GNUC__)
#error Vennominon stat hook self-check requires GCC
#elif __GNUC__
void VennominonTheKingOfPoisonousSnakes_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = VENNOMINON_THE_KING_OF_POISONOUS_SNAKES;
  VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats(&zone);
}
#endif
