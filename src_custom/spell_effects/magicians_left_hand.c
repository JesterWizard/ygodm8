#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void MAGICIANS_LEFT_HAND_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MAGICIANS_LEFT_HAND);

  /* ponytail: negate opponent's first Trap Card/effect each turn (while you
   * control a Spellcaster) then destroy needs a trap-resolve gate + per-turn
   * "first trap used" flag outside this file (no in-file trap negate
   * dispatch; no turn-scoped counter on DuelCard/field).
   * Ceiling: face-up continuous only; upgrade: trap-activate/resolve hook → if
   * face-up MAGICIANS_LEFT_HAND on controller's field, controller has a
   * Spellcaster (Duel_CardHasMonsterType TYPE_SPELLCASTER), and this is the
   * opponent's first trap resolve this turn, then negate and Duel_DestroyZone
   * that trap. */
}

APPEND_TEXT void EffectMAGICIANS_LEFT_HAND(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAGICIANS_LEFT_HAND, MAGICIANS_LEFT_HAND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
