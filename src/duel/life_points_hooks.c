#include "global.h"
#include "configs/runtime.h"

LYN_REPLACE_CHECK(CapLifePointsAfterDuel);
void CapLifePointsAfterDuel__Replacement(void)
{
  gLifePointsOutsideDuel = gDuelLifePoints[DUEL_PLAYER];

  if (gRuntimeConfig.restore_life_points_after_duel == TRUE)
    gLifePointsOutsideDuel = 8000;

  if (gLifePointsOutsideDuel > 8000)
    gLifePointsOutsideDuel = 8000;
}
