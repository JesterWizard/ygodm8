#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void BACKUP_SQUAD_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(BACKUP_SQUAD);

  /* ponytail: continuous face-up only — damage≥1000 draw listener needs a
   * battle/LP-change hook outside this file (no in-file damage dispatch). */
}

APPEND_TEXT void EffectBACKUP_SQUAD(void)
{
  if (Duel_TryResolveSpellThroughTraps(BACKUP_SQUAD, BACKUP_SQUAD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
