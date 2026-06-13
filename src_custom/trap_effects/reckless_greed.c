#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "reckless_greed.h"

void UpdateDuelGfxExceptField(void);

static u8 GetFixedDuelistForTurnRelative(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void DrawOneCardForOwner(u8 owner)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[owner][i].id != CARD_NONE)
      continue;

    TryDrawingCard(owner);
    PlayMusic(SFX_DRAW_CARD);
    UpdateDuelGfxExceptField();
    return;
  }
}

static void DrawTwoCardsForOwner(u8 owner)
{
  DrawOneCardForOwner(owner);
  if (IsDuelOver() == TRUE)
    return;
  DrawOneCardForOwner(owner);
}

static void ActivateRecklessGreedZone(struct DuelCard *zone)
{
  u8 owner = GetFixedDuelistForTurnRelative(INACTIVE_DUELIST);

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = RECKLESS_GREED;
    ActivateCardEffectText();
  }

  DrawTwoCardsForOwner(owner);
  if (IsDuelOver() == TRUE)
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
