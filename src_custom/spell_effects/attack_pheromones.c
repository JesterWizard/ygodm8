#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void ATTACK_PHEROMONES_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(ATTACK_PHEROMONES);

  /* ponytail: Reptile attacks DEF → flip to face-up ATK at end of Damage Step
   * needs a battle_effects / Damage Step end hook outside this file.
   * Ceiling: face-up continuous only; upgrade: end-of-Damage-Step → if face-up
   * ATTACK_PHEROMONES on controller's field, attacker is Reptile
   * (Duel_CardHasMonsterType TYPE_REPTILE), and defender was Defense Position,
   * then set defender isDefending=FALSE and isFaceUp=TRUE. */
}

APPEND_TEXT void EffectATTACK_PHEROMONES(void)
{
  if (Duel_TryResolveSpellThroughTraps(ATTACK_PHEROMONES, ATTACK_PHEROMONES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
