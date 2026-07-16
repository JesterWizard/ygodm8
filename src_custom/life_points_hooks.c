#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "debug_ruleset.h"
#include "timed_duel.h"
#include "mechanics_tutorial.h"
#include "duel.h"

extern u32 gLifePointsOutsideDuel;

static unsigned GetLifePointsOutsideDuel(void) {
  return gLifePointsOutsideDuel;
}

LYN_REPLACE_CHECK(InitDuelLifePoints);
void InitDuelLifePoints__Replacement(void) {
  if (TimedDuel_IsActive() == TRUE) {
    TimedDuel_ApplyLifePointsIfActive();
    return;
  }
  if (MechanicsTutorial_IsActive() == TRUE) {
    MechanicsTutorial_ApplyLifePointsIfActive();
    return;
  }

  if (DebugRuleset_IsDuelistKingdom()) {
    gDuelLifePoints[DUEL_PLAYER] = DEBUG_RULESET_DUELIST_KINGDOM_LP;
    gDuelLifePoints[DUEL_OPPONENT] = DEBUG_RULESET_DUELIST_KINGDOM_LP;
    return;
  }

  if (gDuelType == DUEL_TYPE_INGAME) {
    gDuelLifePoints[DUEL_PLAYER] = GetLifePointsOutsideDuel();
    gDuelLifePoints[DUEL_OPPONENT] = gDuelData.duelist.lifePoints;
  } else {
    gDuelLifePoints[DUEL_PLAYER] = gDuelData.duelist.playerLp;
    gDuelLifePoints[DUEL_OPPONENT] = gDuelData.duelist.lifePoints;
  }
}

LYN_REPLACE_CHECK(InitLifePoints);
void InitLifePoints__Replacement(void) {
  if (gRuntimeConfig.set_life_points_after_duel != 0)
    gLifePointsOutsideDuel = gRuntimeConfig.set_life_points_after_duel;
  else
    gLifePointsOutsideDuel = 8000;
}

LYN_REPLACE_CHECK(CapLifePointsAfterDuel);
void CapLifePointsAfterDuel__Replacement(void) {
  if (gRuntimeConfig.set_life_points_after_duel != 0) {
    gLifePointsOutsideDuel = gRuntimeConfig.set_life_points_after_duel;
    return;
  }

  gLifePointsOutsideDuel = gDuelLifePoints[DUEL_PLAYER];

  if (gRuntimeConfig.restore_life_points_after_duel == TRUE
      && !(gRuntimeConfig.preserve_life_points_above_8000_after_duel == TRUE && gLifePointsOutsideDuel > 8000))
    gLifePointsOutsideDuel = 8000;

  if (gLifePointsOutsideDuel > 8000
      && gRuntimeConfig.cap_life_points_after_duel == FALSE
      && gRuntimeConfig.preserve_life_points_above_8000_after_duel == FALSE)
    gLifePointsOutsideDuel = 8000;
}
