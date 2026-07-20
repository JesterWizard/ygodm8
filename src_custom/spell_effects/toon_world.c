#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define TOON_WORLD_LP_COST 1000

static u8 CanActivateToonWorld(void)
{
  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= TOON_WORLD_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= TOON_WORLD_LP_COST;
}

static void TOON_WORLD_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateToonWorld())
    return;

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -TOON_WORLD_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(TOON_WORLD);
}

APPEND_TEXT void EffectTOON_WORLD(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(TOON_WORLD, TOON_WORLD_LP_COST, TOON_WORLD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
