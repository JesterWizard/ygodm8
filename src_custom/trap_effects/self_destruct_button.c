#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "self_destruct_button.h"

u8 CanActivateSelfDestructButton(void)
{
  u16 ownerLp;
  u16 opponentLp;

  if (WhoseTurn() == DUEL_PLAYER) {
    ownerLp = gDuelLifePoints[DUEL_OPPONENT];
    opponentLp = gDuelLifePoints[DUEL_PLAYER];
  } else {
    ownerLp = gDuelLifePoints[DUEL_PLAYER];
    opponentLp = gDuelLifePoints[DUEL_OPPONENT];
  }

  if (ownerLp >= opponentLp)
    return FALSE;

  return (opponentLp - ownerLp) >= SELF_DESTRUCT_BUTTON_LP_DIFFERENCE;
}

u8 IsActivatedSelfDestructButtonZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == SELF_DESTRUCT_BUTTON && zone->isFaceUp == TRUE;
}

static void ActivateSelfDestructButtonZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(SELF_DESTRUCT_BUTTON, 3);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)gDuelLifePoints[WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT],
                    FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ChangeLp(INACTIVE_DUELIST,
                -(s32)gDuelLifePoints[WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER], FALSE);
}

void TryActivateSelfDestructButtonOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  if (!CanActivateSelfDestructButton())
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != SELF_DESTRUCT_BUTTON || zone->isFaceUp != FALSE)
      continue;

    ActivateSelfDestructButtonZone(zone);
    return;
  }
}
