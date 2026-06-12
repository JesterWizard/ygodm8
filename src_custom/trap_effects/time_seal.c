#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "time_seal.h"

static void ActivateTimeSealZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = TIME_SEAL;
    ActivateCardEffectText();
  }

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
