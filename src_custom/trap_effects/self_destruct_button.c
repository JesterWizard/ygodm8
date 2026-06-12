#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "self_destruct_button.h"

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

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

static void ApplySelfDestructButtonEffect(void)
{
  SetPlayerLifePointsToSubtract(gDuelLifePoints[DUEL_PLAYER]);
  SetOpponentLifePointsToSubtract(gDuelLifePoints[DUEL_OPPONENT]);
  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void ActivateSelfDestructButtonZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SELF_DESTRUCT_BUTTON;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  ApplySelfDestructButtonEffect();
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
