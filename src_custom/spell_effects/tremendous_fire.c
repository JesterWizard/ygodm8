#include "global.h"
#include "common-chax.h"
#include "dark_room_of_nightmare.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define TREMENDOUS_FIRE_DAMAGE 1000

static void TremendousFire_ResolveBody(void)
{
  if (Duel_ResolveBurnSpell(TREMENDOUS_FIRE, TREMENDOUS_FIRE_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  ResolveDarkRoomEffect();
}

LYN_REPLACE_CHECK(EffectTremendousFire);
APPEND_TEXT void EffectTremendousFire__Replacement(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(TREMENDOUS_FIRE, TREMENDOUS_FIRE_DAMAGE,
                                         TremendousFire_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
