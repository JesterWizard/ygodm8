#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void LIGHT_BARRIER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LIGHT_BARRIER);

  /* ponytail: Standby coin (Tails → negate until next Standby), Arcana Force
   * summon choose-without-coin, and battle-destroy LP gain need turn_effect /
   * summon / battle_effects hooks outside this file.
   * Ceiling: continuous face-up only (Arcana Reading already checks face-up
   * LIGHT_BARRIER for choose-Heads path); upgrade:
   * TryApplyLightBarrierStandbyCoin → if Tails set negated flag;
   * Arcana Force on-summon → if face-up LIGHT_BARRIER && !negated then
   * PlayerChoosesCoinEffect; battle destroy → if Arcana Force destroyed opp
   * by battle && face-up LIGHT_BARRIER && !negated then
   * Duel_ChangeLp(controller, +destroyedOriginalAtk). */
}

APPEND_TEXT void EffectLIGHT_BARRIER(void)
{
  if (Duel_TryResolveSpellThroughTraps(LIGHT_BARRIER, LIGHT_BARRIER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
