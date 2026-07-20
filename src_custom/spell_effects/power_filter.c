#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void POWER_FILTER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(POWER_FILTER);

  /* ponytail: SS lock for monsters with ATK ≤1000 needs a CanSpecialSummon /
   * PlaceMonster gate outside this file (no in-file summon dispatch).
   * Ceiling: continuous face-up only; upgrade: LynJump Duel_CardCannotBeSpecialSummoned
   * (or PlaceMonsterFromId) → if face-up POWER_FILTER on field and printed ATK ≤1000
   * then block. */
}

APPEND_TEXT void EffectPOWER_FILTER(void)
{
  if (Duel_TryResolveSpellThroughTraps(POWER_FILTER, POWER_FILTER_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
