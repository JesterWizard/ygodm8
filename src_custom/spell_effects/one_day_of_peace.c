#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_ops.h"
#include "spell_effects.h"

#define ONE_DAY_OF_PEACE_DRAW_COUNT 1

static void ONE_DAY_OF_PEACE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(ONE_DAY_OF_PEACE);

  if (IsDuelOver() == TRUE)
    return;

  if (Op_Draw(ACTIVE_DUELIST, ONE_DAY_OF_PEACE_DRAW_COUNT, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Op_Draw(INACTIVE_DUELIST, ONE_DAY_OF_PEACE_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: neither player takes damage until end of opponent's next turn
   * needs an LP/damage gate outside this file (no damage-immunity helper).
   * Ceiling: both draw only; upgrade: turn_effect / ChangeLp hook → skip damage
   * while One Day of Peace lock is active through opponent's next End Phase. */

  Op_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectONE_DAY_OF_PEACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ONE_DAY_OF_PEACE, ONE_DAY_OF_PEACE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
