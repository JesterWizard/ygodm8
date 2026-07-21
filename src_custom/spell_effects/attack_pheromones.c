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
}

APPEND_TEXT void EffectATTACK_PHEROMONES(void)
{
  if (Duel_TryResolveSpellThroughTraps(ATTACK_PHEROMONES, ATTACK_PHEROMONES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
