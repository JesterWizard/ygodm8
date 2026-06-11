#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "jar_of_greed.h"

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

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gDuel.hands[owner][i].id != CARD_NONE)
      continue;

    TryDrawingCard(owner);
    PlayMusic(SFX_DRAW_CARD);
    UpdateDuelGfxExceptField();
    return;
  }
}

static void ActivateJarOfGreedZone(struct DuelCard *zone)
{
  u8 owner = GetFixedDuelistForTurnRelative(INACTIVE_DUELIST);

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = JAR_OF_GREED;
    ActivateCardEffectText();
  }

  DrawOneCardForOwner(owner);
}

void TryActivateJarOfGreedOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != JAR_OF_GREED || zone->isFaceUp != FALSE)
      continue;

    ActivateJarOfGreedZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
