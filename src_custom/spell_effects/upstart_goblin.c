#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define UPSTART_GOBLIN_LP 1000

static void UpstartGoblin_ResolveBody(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, UPSTART_GOBLIN_LP, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(UPSTART_GOBLIN);
}

APPEND_TEXT void EffectUpstartGoblin(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(UPSTART_GOBLIN, UPSTART_GOBLIN_LP, UpstartGoblin_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
