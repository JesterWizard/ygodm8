#include "global.h"
#include "common-chax.h"
#include "amazoness_call.h"
#include "amazoness_secret_arts.h"
#include "arcana_reading.h"
#include "arcana_spread.h"
#include "contact_gate.h"
#include "constants/card_ids.h"
#include "en_shuffle.h"
#include "evil_assault.h"
#include "expanded_graveyard.h"
#include "gy_ignition.h"
#include "soul_servant.h"

u8 CanActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex);
void ActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateDestinyHeroMaliciousGy(u8 fixedDuelist, u8 gyIndex);
void ActivateDestinyHeroMaliciousGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateMezukiGy(u8 fixedDuelist, u8 gyIndex);
void ActivateMezukiGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateEvilHeroSinisterNecromGy(u8 fixedDuelist, u8 gyIndex);
void ActivateEvilHeroSinisterNecromGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateLevelEaterGy(u8 fixedDuelist, u8 gyIndex);
void ActivateLevelEaterGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivatePoseidraTheAtlanteanDragonGy(u8 fixedDuelist, u8 gyIndex);
void ActivatePoseidraTheAtlanteanDragonGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateYamorimoriGy(u8 fixedDuelist, u8 gyIndex);
void ActivateYamorimoriGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex);
void ActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex);
u8 CanActivateDestinyHeroDynatagGy(u8 fixedDuelist, u8 gyIndex);
void ActivateDestinyHeroDynatagGy(u8 fixedDuelist, u8 gyIndex);

struct GyIgnitionEntry {
  u16 cardId;
  u8 (*can)(u8 fixedDuelist, u8 gyIndex);
  void (*activate)(u8 fixedDuelist, u8 gyIndex);
};

static const struct GyIgnitionEntry sGyIgnitionTable[] APPEND_RODATA = {
  { THE_WHITE_STONE_OF_ANCIENTS,
    CanActivateTheWhiteStoneOfAncientsGy,
    ActivateTheWhiteStoneOfAncientsGy },
  { AMAZONESS_CALL,
    CanActivateAmazonessCallGy,
    ActivateAmazonessCallGy },
  { AMAZONESS_SECRET_ARTS,
    CanActivateAmazonessSecretArtsGy,
    ActivateAmazonessSecretArtsGy },
  { ARCANA_READING,
    CanActivateArcanaReadingGy,
    ActivateArcanaReadingGy },
  { ARCANA_SPREAD,
    CanActivateArcanaSpreadGy,
    ActivateArcanaSpreadGy },
  { CONTACT_GATE,
    CanActivateContactGateGy,
    ActivateContactGateGy },
  { EN_SHUFFLE,
    CanActivateEnShuffleGy,
    ActivateEnShuffleGy },
  { EVIL_ASSAULT,
    CanActivateEvilAssaultGy,
    ActivateEvilAssaultGy },
  { SOUL_SERVANT,
    CanActivateSoulServantGy,
    ActivateSoulServantGy },
  { DESTINY_HERO_MALICIOUS,
    CanActivateDestinyHeroMaliciousGy,
    ActivateDestinyHeroMaliciousGy },
  { MEZUKI,
    CanActivateMezukiGy,
    ActivateMezukiGy },
  { EVIL_HERO_SINISTER_NECROM,
    CanActivateEvilHeroSinisterNecromGy,
    ActivateEvilHeroSinisterNecromGy },
  { LEVEL_EATER,
    CanActivateLevelEaterGy,
    ActivateLevelEaterGy },
  { POSEIDRA_THE_ATLANTEAN_DRAGON,
    CanActivatePoseidraTheAtlanteanDragonGy,
    ActivatePoseidraTheAtlanteanDragonGy },
  { YAMORIMORI,
    CanActivateYamorimoriGy,
    ActivateYamorimoriGy },
  { DESTINY_HERO_CELESTIAL,
    CanActivateDestinyHeroCelestialGy,
    ActivateDestinyHeroCelestialGy },
  { DESTINY_HERO_DYNATAG,
    CanActivateDestinyHeroDynatagGy,
    ActivateDestinyHeroDynatagGy },
};

u8 GyIgnition_TryAt(u8 fixedDuelist, u16 cardId)
{
  const struct GyIgnitionEntry *entry = NULL;
  u8 i;
  u8 gyCount;

  if (cardId == CARD_NONE || !GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sGyIgnitionTable); i++) {
    if (sGyIgnitionTable[i].cardId == cardId) {
      entry = &sGyIgnitionTable[i];
      break;
    }
  }

  if (entry == NULL)
    return FALSE;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != cardId)
      continue;

    if (!entry->can(fixedDuelist, i))
      continue;

    entry->activate(fixedDuelist, i);
    return TRUE;
  }

  return FALSE;
}
