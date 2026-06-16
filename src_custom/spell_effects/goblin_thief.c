#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define GOBLIN_THIEF_LP 500

static void GoblinThief_ResolveBody(void)
{
  if (Duel_ChangeLp(INACTIVE_DUELIST, -GOBLIN_THIEF_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, GOBLIN_THIEF_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(GOBLIN_THIEF);
}

APPEND_TEXT void EffectGoblinThief(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(GOBLIN_THIEF, GOBLIN_THIEF_LP, GoblinThief_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
