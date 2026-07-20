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

  /* ponytail: Amazoness vs higher-ATK +1000 during damage calculation only needs a
   * battle_effects damage-calc hook (like skyscraper.c) outside this file.
   * Ceiling: face-up continuous only; upgrade: ApplyAmazonessFightingSpiritBattleAtkBoost
   * → if face-up AMAZONESS_FIGHTING_SPIRIT on controller's field, attacker passes
   * Duel_IsAmazonessCard, and defender ATK > attacker ATK, then attacker ATK += 1000. */
}

APPEND_TEXT void EffectAMAZONESS_FIGHTING_SPIRIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_FIGHTING_SPIRIT,
                                       AMAZONESS_FIGHTING_SPIRIT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
