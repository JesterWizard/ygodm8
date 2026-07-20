#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

#define CLOCK_TOWER_PRISON_MAX_COUNTERS 4

/* ponytail: Opp Standby Clock Counter placement needs a turn_effect Standby
 * hook outside this file (no in-file Standby dispatch).
 * Ceiling: continuous face-up + unk4 counter slot (never rises alone);
 * upgrade: opp Standby → if face-up CLOCK_TOWER_PRISON then unk4++
 * (cap CLOCK_TOWER_PRISON_MAX_COUNTERS). */

/* ponytail: 4+ counters → no battle damage needs a battle-damage gate outside
 * this file. Ceiling: continuous only; upgrade: battle LP calc → if face-up
 * CLOCK_TOWER_PRISON with unk4 >= 4 then battle damage to controller = 0. */

/* ponytail: destroy with 4+ counters → SS Destiny HERO - Dreadmaster from
 * hand/Deck needs a destroy/leave-field hook outside this file.
 * Ceiling: continuous face-up only; upgrade: OnDestroy → if unk4 >= 4 then
 * Duel_SpecialSummonFromHand/Deck(DESTINY_HERO_DREADMASTER). */

APPEND_TEXT void EffectCLOCK_TOWER_PRISON(void)
{
  const struct EffectScript *script =
      EffectScript_Find(CLOCK_TOWER_PRISON, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CLOCK_TOWER_PRISON_SelfCheck(void)
{
  if (CLOCK_TOWER_PRISON_MAX_COUNTERS != 4)
    while (1)
      ;
  if (DESTINY_HERO_DREADMASTER == CARD_NONE)
    while (1)
      ;
}
#endif
