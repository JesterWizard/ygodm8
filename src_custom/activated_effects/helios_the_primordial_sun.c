#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 CountBanishedMonsters(void)
{
  u8 total = 0;
  u8 d;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (d = 0; d < 2; d++) {
    for (i = 0; i < RemovedFromPlay_GetCount(d); i++) {
      if (GetTypeGroup(RemovedFromPlay_GetCardAt(d, i)) == TYPE_GROUP_MONSTER)
        total++;
    }
  }

  return total;
}

unsigned char CanActivateHELIOS_THE_PRIMORDIAL_SUN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HELIOS_THE_PRIMORDIAL_SUN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HELIOS_THE_PRIMORDIAL_SUN)
    return FALSE;

  /* ponytail: continuous ATK/DEF = banished×100 needs permanent overlay.
   * Ceiling: OPT stages ≈ (banished×100)/500. */
  return CanUseMonsterEffect(zone);
}

void ActivateHELIOS_THE_PRIMORDIAL_SUNEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 banished;
  u8 stages;

  Duel_ShowEffectTextTyped(HELIOS_THE_PRIMORDIAL_SUN, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  banished = CountBanishedMonsters();
  stages = (u8)((banished * 100) / 500);
  if (stages > 20)
    stages = 20;

  SetPermStage(zone, stages);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
