#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

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
