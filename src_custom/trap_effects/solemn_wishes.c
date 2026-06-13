#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "solemn_wishes.h"

#define SOLEMN_WISHES_LP 500

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

static u8 BackrowForDuelist(u8 duelist)
{
  return (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 HasSolemnWishesActive(u8 duelist)
{
  u8 i;
  u8 backrow = BackrowForDuelist(duelist);
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id == SOLEMN_WISHES && zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static void ApplySolemnWishesLpGain(u8 duelist)
{
  if (duelist == DUEL_PLAYER)
    SetPlayerLifePointsToAdd(SOLEMN_WISHES_LP);
  else
    SetOpponentLifePointsToAdd(SOLEMN_WISHES_LP);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (IsDuelOver() == TRUE)
    return;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SOLEMN_WISHES;
    ActivateCardEffectText();
  }
}

static void ActivateSolemnWishesZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
}

static u8 TryFlipFaceDownSolemnWishesOnDraw(u8 duelist)
{
  u8 i;
  u8 backrow = BackrowForDuelist(duelist);
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id != SOLEMN_WISHES || zone->isFaceUp != FALSE)
      continue;

    ActivateSolemnWishesZone(zone);
    return TRUE;
  }

  return FALSE;
}

static u8 TryAutoPlaceDrawnSolemnWishes(u8 duelist, u8 handSlot)
{
  s8 backrowCol;
  u8 backrow = BackrowForDuelist(duelist);
  struct DuelCard *handCard = &gDuel.hands[duelist][handSlot];
  struct DuelCard *fieldZone;

  if (handCard->id != SOLEMN_WISHES)
    return FALSE;

  backrowCol = FirstEmptyZoneInRow(gFixedZones[backrow]);
  if (backrowCol < 0)
    return FALSE;

  fieldZone = gFixedZones[backrow][backrowCol];
  fieldZone->id = SOLEMN_WISHES;
  handCard->id = CARD_NONE;
  ResetPermStage(fieldZone);
  ResetTempStage(fieldZone);
  ActivateSolemnWishesZone(fieldZone);
  return TRUE;
}

void TryApplySolemnWishesOnDraw(u8 duelist, u16 cardDrawn, u8 handSlot)
{
  /* ponytail: InitBoard fills hands via TryDrawingCard before duel gfx; skip until past opening hand. */
  if (gDuelDecks[duelist].cardsDrawn <= MAX_ZONES_IN_ROW)
    return;

  if (cardDrawn == SOLEMN_WISHES)
    TryAutoPlaceDrawnSolemnWishes(duelist, handSlot);
  else
    TryFlipFaceDownSolemnWishesOnDraw(duelist);

  if (!HasSolemnWishesActive(duelist))
    return;

  ApplySolemnWishesLpGain(duelist);
}
