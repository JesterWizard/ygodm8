#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

static u16 AirNeosLpGapBonus(u8 controller)
{
  u8 opponent = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u16 ownerLp = gDuelLifePoints[controller];
  u16 oppLp = gDuelLifePoints[opponent];

  if (ownerLp >= oppLp)
    return 0;

  return oppLp - ownerLp;
}

static u16 AirNeosCurrentAtk(struct DuelCard *zone)
{
  u8 controller = GetDuelistForZone(zone);
  u32 baseAtk = gCardData_NEW[zone->id].atk;
  u16 bonus = 0;

  if (controller != 0xFF)
    bonus = AirNeosLpGapBonus(controller);

  return Duel_ClampStat(baseAtk + bonus);
}

u8 ElementalHeroAirNeos_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_AIR_NEOS)
    return FALSE;

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, AirNeosCurrentAtk(zone), gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateELEMENTAL_HERO_AIR_NEOS(void)
{
  /* ponytail: End Phase shuffle to Extra Deck needs turn_effect hook — ApplyDynamicZoneStats only. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateELEMENTAL_HERO_AIR_NEOS(void)
{
}

#if !defined(__GNUC__)
#error Elemental HERO Air Neos stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroAirNeos_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_AIR_NEOS;
  ElementalHeroAirNeos_ApplyDynamicZoneStats(&zone);
}
#endif
