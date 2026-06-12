#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "secret_barrel.h"

#define SECRET_BARREL_DAMAGE_PER_CARD 200

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

static u8 CountActiveDuelistFieldAndHandCards(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      count++;
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id != CARD_NONE)
      count++;
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static void ApplySecretBarrelDamage(u8 cardCount)
{
  u16 damage;

  if (cardCount == 0)
    return;

  damage = (u16)cardCount * SECRET_BARREL_DAMAGE_PER_CARD;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(damage);
  else
    SetOpponentLifePointsToSubtract(damage);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void ActivateSecretBarrelZone(struct DuelCard *zone)
{
  u8 cardCount = CountActiveDuelistFieldAndHandCards();

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SECRET_BARREL;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  ApplySecretBarrelDamage(cardCount);
}

void TryActivateSecretBarrelOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != SECRET_BARREL || zone->isFaceUp != FALSE)
      continue;

    ActivateSecretBarrelZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
