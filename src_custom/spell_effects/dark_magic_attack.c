#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

u8 CanActivateDARK_MAGIC_ATTACK(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN);
}

APPEND_TEXT void EffectDARK_MAGIC_ATTACK(void)
{
  const struct EffectScript *script =
      EffectScript_Find(DARK_MAGIC_ATTACK, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
