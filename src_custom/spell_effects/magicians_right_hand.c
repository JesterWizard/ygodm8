#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void MAGICIANS_RIGHT_HAND_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MAGICIANS_RIGHT_HAND);

  /* ponytail: negate opponent's first Spell Card/effect each turn (while you
   * control a Spellcaster) then destroy needs a spell-resolve gate + per-turn
   * "first spell used" flag outside this file (no in-file spell negate
   * dispatch; no turn-scoped counter on DuelCard/field).
   * Ceiling: face-up continuous only; upgrade: spell-activate/resolve hook → if
   * face-up MAGICIANS_RIGHT_HAND on controller's field, controller has a
   * Spellcaster (Duel_CardHasMonsterType TYPE_SPELLCASTER), and this is the
   * opponent's first spell resolve this turn, then negate and Duel_DestroyZone
   * that spell (or destroy if it had no effect). */
}

APPEND_TEXT void EffectMAGICIANS_RIGHT_HAND(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAGICIANS_RIGHT_HAND, MAGICIANS_RIGHT_HAND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
