#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(CONTINUOUS_DESTRUCTION_PUNCH);

  /* ponytail: post-damage-calc "DEF > ATK → destroy attacker" needs a
   * battle_effects hook (clone des_kangaroo.c MarkPendingAttackerDestroy) outside
   * this file. Ceiling: continuous face-up only; upgrade: after damage calc, if
   * face-up CONTINUOUS_DESTRUCTION_PUNCH on defender's controller, defender is
   * DEF position, and defender DEF > attacker ATK, destroy attacker (damage normal). */
}

APPEND_TEXT void EffectCONTINUOUS_DESTRUCTION_PUNCH(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTINUOUS_DESTRUCTION_PUNCH,
                                       CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
