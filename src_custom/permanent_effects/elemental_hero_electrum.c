#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_electrum.h"

#define ELECTRUM_BASE_ATK 2900
#define ELECTRUM_ATK_PER_SHARED_ATTRIBUTE_MONSTER 300

static u8 ElectrumAttributeMatches(u8 attribute)
{
  return attribute == ATTRIBUTE_LIGHT
      || attribute == ATTRIBUTE_WIND
      || attribute == ATTRIBUTE_WATER
      || attribute == ATTRIBUTE_FIRE
      || attribute == ATTRIBUTE_EARTH;
}

static u8 MonsterSharesElectrumAttribute(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  SetCardInfo(zone->id);
  return ElectrumAttributeMatches(gCardInfo.attribute);
}

static u8 CountOpponentMonstersSharingElectrumAttribute(struct DuelCard *electrumZone)
{
  u8 fixedRow = Duel_OpponentMonsterRowForZone(electrumZone);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (MonsterSharesElectrumAttribute(gFixedZones[fixedRow][col]))
      count++;
  }

  return count;
}

static u16 ElectrumCurrentAtk(struct DuelCard *zone)
{
  return Duel_StatFromCount(
      CountOpponentMonstersSharingElectrumAttribute(zone),
      ELECTRUM_ATK_PER_SHARED_ATTRIBUTE_MONSTER,
      ELECTRUM_BASE_ATK);
}

u8 ElementalHeroElectrum_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;
  u16 def;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_ELECTRUM)
    return FALSE;

  SetCardInfo(zone->id);
  def = gCardInfo.def;
  atk = ElectrumCurrentAtk(zone);
  Duel_WriteCardInfoStats(zone->id, atk, def);
  return TRUE;
}

void ElementalHeroElectrum_ReturnRemovedMonstersToDecks(void)
{
  /* No removed-from-play zone yet — shuffle banished/exiled monsters
   * back into each owner's deck once Duel_BanishZone exists. ATK overlay via
   * ElementalHeroElectrum_ApplyDynamicZoneStats. */
}

void ElementalHeroElectrum_OnFusionSummoned(void)
{
  Duel_ShowEffectText(ELEMENTAL_HERO_ELECTRUM);
  if (IsDuelOver() == TRUE)
    return;

  ElementalHeroElectrum_ReturnRemovedMonstersToDecks();
}

#if !defined(__GNUC__)
#error Elemental HERO Electrum stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroElectrum_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_ELECTRUM;
  ElementalHeroElectrum_ApplyDynamicZoneStats(&zone);
}
#endif
