#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define SPARKS_DAMAGE 200

static void Sparks_ResolveBody(void)
{
  if (Duel_ResolveBurnSpell(SPARKS, SPARKS_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

LYN_REPLACE_CHECK(EffectSparks);
APPEND_TEXT void EffectSparks__Replacement(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(SPARKS, SPARKS_DAMAGE, Sparks_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
