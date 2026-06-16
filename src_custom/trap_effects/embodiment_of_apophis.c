#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "embodiment_of_apophis.h"

APPEND_TEXT void EffectEmbodimentOfApophis(void)
{
  struct DuelCard *trapZone;
  struct DuelCard *monsterZone;

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  monsterZone = EmbodimentOfApophisMonsterZoneForTrap(trapZone);

  if (monsterZone == NULL || EmbodimentOfApophisTrapZoneIsAwakened(trapZone))
    return;

  FlipCardFaceUp(trapZone);
  trapZone->isLocked = TRUE;

  monsterZone->id = EMBODIMENT_OF_APOPHIS;
  InitEmbodimentOfApophisMonsterZone(monsterZone);
  RegisterEmbodimentOfApophisLinkFromZones(trapZone, monsterZone);

  Duel_ShowEffectText(EMBODIMENT_OF_APOPHIS);
}
