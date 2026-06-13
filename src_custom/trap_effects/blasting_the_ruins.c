#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "blasting_the_ruins.h"

#define BLASTING_THE_RUINS_DAMAGE 3000
#define BLASTING_THE_RUINS_MAX_DECK_CARDS 10

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);
int NumCardsInDeck(unsigned char);
int GetCardsDrawn(unsigned char);

static u8 OwnerDeckHasAtMostTenCards(u8 owner)
{
  u16 remaining = NumCardsInDeck(owner);

  if (remaining >= GetCardsDrawn(owner))
    remaining -= GetCardsDrawn(owner);
  else
    remaining = 0;

  return remaining <= BLASTING_THE_RUINS_MAX_DECK_CARDS;
}

static void ApplyBlastingTheRuinsDamage(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(BLASTING_THE_RUINS_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(BLASTING_THE_RUINS_DAMAGE);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void ActivateBlastingTheRuinsZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = BLASTING_THE_RUINS;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  ApplyBlastingTheRuinsDamage();
}

void TryActivateBlastingTheRuinsOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  if (!OwnerDeckHasAtMostTenCards(INACTIVE_DUELIST))
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != BLASTING_THE_RUINS || zone->isFaceUp != FALSE)
      continue;

    ActivateBlastingTheRuinsZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
