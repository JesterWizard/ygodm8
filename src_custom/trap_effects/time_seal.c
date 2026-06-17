#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "time_seal.h"

static void ActivateTimeSealZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(TIME_SEAL, 3);
  gTimeSealSkipDrawDuelist = WhoseTurn();
}

void ResetTimeSealSkipDraw(void)
{
  gTimeSealSkipDrawDuelist = TIME_SEAL_SKIP_DRAW_NONE;
}

u8 ShouldSkipDrawPhaseForTimeSeal(u8 turn)
{
  return gTimeSealSkipDrawDuelist == turn;
}

void ConsumeTimeSealSkipDraw(u8 turn)
{
  if (gTimeSealSkipDrawDuelist == turn)
    gTimeSealSkipDrawDuelist = TIME_SEAL_SKIP_DRAW_NONE;
}

void TryActivateTimeSealOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != TIME_SEAL || zone->isFaceUp != FALSE)
      continue;

    ActivateTimeSealZone(zone);
    return;
  }
}
