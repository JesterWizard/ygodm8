#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mirror_force.h"

APPEND_TEXT void EffectMirrorForce(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id == CARD_NONE)
      continue;
    if (zone->isDefending)
      continue;
    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);

  Duel_ShowTrapResponseText(MIRROR_FORCE, gTrapEffectData.originCardId);
}
