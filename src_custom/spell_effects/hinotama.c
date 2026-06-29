#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define HINOTAMA_DAMAGE 500

static void Hinotama_ResolveBody(void)
{
  Duel_ShowEffectText(HINOTAMA);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -HINOTAMA_DAMAGE, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
}

LYN_REPLACE_CHECK(EffectHinotama);
APPEND_TEXT void EffectHinotama__Replacement(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(HINOTAMA, HINOTAMA_DAMAGE, Hinotama_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
