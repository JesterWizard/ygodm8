#include "global.h"
#include "common-chax.h"
#include "chimeratech_fusion_stats.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"

#define CHIMERATECH_FORTRESS_ATK_PER_MATERIAL 1000
#define CHIMERATECH_MEGAFLEET_ATK_PER_MATERIAL 1200

void ChimeratechFusion_StampMaterialCount(struct DuelCard *zone, u8 materialCount)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (materialCount < 2)
    materialCount = 2;
  if (materialCount > FUSION_MAX_MATERIALS)
    materialCount = FUSION_MAX_MATERIALS;

  zone->permStage = (s8)materialCount;
}

u8 ChimeratechFortressDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 count;
  u16 atk;

  if (zone == NULL || zone->id != CHIMERATECH_FORTRESS_DRAGON)
    return FALSE;

  count = (u8)zone->permStage;
  if (count < 2)
    count = 2;

  atk = Duel_StatFromCount(count, CHIMERATECH_FORTRESS_ATK_PER_MATERIAL, 0);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

u8 ChimeratechMegafleetDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 count;
  u16 atk;

  if (zone == NULL || zone->id != CHIMERATECH_MEGAFLEET_DRAGON)
    return FALSE;

  count = (u8)zone->permStage;
  if (count < 2)
    count = 2;

  atk = Duel_StatFromCount(count, CHIMERATECH_MEGAFLEET_ATK_PER_MATERIAL, 0);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ChimeratechFusionStats_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = CHIMERATECH_FORTRESS_DRAGON;
  zone.permStage = 3;
  SetCardInfo(zone.id);
  ChimeratechFortressDragon_ApplyDynamicZoneStats(&zone);
  if (gCardInfo.atk != 3000)
    while (1)
      ;

  zone.id = CHIMERATECH_MEGAFLEET_DRAGON;
  zone.permStage = 4;
  SetCardInfo(zone.id);
  ChimeratechMegafleetDragon_ApplyDynamicZoneStats(&zone);
  if (gCardInfo.atk != 4800)
    while (1)
      ;
}
#endif
