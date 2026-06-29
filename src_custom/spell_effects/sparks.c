#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define SPARKS_DAMAGE 200

static void Sparks_ResolveBody(void)
{
  Duel_ShowEffectText(SPARKS);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -SPARKS_DAMAGE, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
}

LYN_REPLACE_CHECK(EffectSparks);
APPEND_TEXT void EffectSparks__Replacement(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(SPARKS, SPARKS_DAMAGE, Sparks_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
