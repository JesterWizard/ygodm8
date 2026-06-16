#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "reckless_greed.h"

static void ActivateRecklessGreedZone(struct DuelCard *zone)
{
  u8 owner = (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
      ? DUEL_PLAYER : DUEL_OPPONENT;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(RECKLESS_GREED, 3);

  if (Duel_DrawCards(INACTIVE_DUELIST, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  gRecklessGreedSkipDrawDuelist = owner;
  gRecklessGreedSkipDrawRemaining = 2;
}

void ResetRecklessGreedSkipDraw(void)
{
  gRecklessGreedSkipDrawDuelist = RECKLESS_GREED_SKIP_DRAW_NONE;
  gRecklessGreedSkipDrawRemaining = 0;
}

u8 ShouldSkipDrawPhaseForRecklessGreed(u8 turn)
{
  return gRecklessGreedSkipDrawDuelist == turn && gRecklessGreedSkipDrawRemaining > 0;
}

void ConsumeRecklessGreedSkipDraw(u8 turn)
{
  if (gRecklessGreedSkipDrawDuelist != turn || gRecklessGreedSkipDrawRemaining == 0)
    return;

  gRecklessGreedSkipDrawRemaining--;
  if (gRecklessGreedSkipDrawRemaining == 0)
    gRecklessGreedSkipDrawDuelist = RECKLESS_GREED_SKIP_DRAW_NONE;
}

void TryActivateRecklessGreedOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != RECKLESS_GREED || zone->isFaceUp != FALSE)
      continue;

    ActivateRecklessGreedZone(zone);
    return;
  }
}
