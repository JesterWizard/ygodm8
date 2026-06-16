#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define OOKAZI_DAMAGE 800

static void Ookazi_ResolveBody(void)
{
  if (Duel_ChangeLp(INACTIVE_DUELIST, -OOKAZI_DAMAGE, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(OOKAZI);
}

LYN_REPLACE_CHECK(EffectOokazi);
APPEND_TEXT void EffectOokazi__Replacement(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(OOKAZI, OOKAZI_DAMAGE, Ookazi_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
