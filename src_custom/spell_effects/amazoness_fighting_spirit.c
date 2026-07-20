#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void AMAZONESS_FIGHTING_SPIRIT_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AMAZONESS_FIGHTING_SPIRIT);
  /* Battle ATK boost: ApplyAmazonessFightingSpiritBattleAtkBoost via ON_DAMAGE_CALC. */
}

APPEND_TEXT void EffectAMAZONESS_FIGHTING_SPIRIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_FIGHTING_SPIRIT,
                                       AMAZONESS_FIGHTING_SPIRIT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
