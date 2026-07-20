#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectURGENT_TUNING(void)
{
  Duel_ShowTrapResponseText(URGENT_TUNING, gTrapEffectData.originCardId);

  /* ponytail: Synchro Summon during Battle Phase needs Synchro material/ED
   * summon path outside this file (no in-file Synchro API).
   * Ceiling: shows text + self-destroy; upgrade: collect Tuners + non-Tuners
   * → Extra Deck Synchro SS. */

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
