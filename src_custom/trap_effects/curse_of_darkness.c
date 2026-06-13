#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "curse_of_darkness.h"

#define CURSE_OF_DARKNESS_DAMAGE 1000

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

static u8 IsCurseOfDarknessActiveOnField(void)
{
  u8 row;
  u8 i;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsActivatedCurseOfDarknessZone(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 IsActivatedCurseOfDarknessZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == CURSE_OF_DARKNESS && zone->isFaceUp == TRUE;
}

static void ApplyCurseOfDarknessDamage(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(CURSE_OF_DARKNESS_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(CURSE_OF_DARKNESS_DAMAGE);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

void TryApplyCurseOfDarknessSpellDamage(void)
{
  if (gHideEffectText)
    return;

  if (!IsCurseOfDarknessActiveOnField())
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(3);
  gCardEffectTextData.cardId = CURSE_OF_DARKNESS;
  ActivateCardEffectText();

  if (IsDuelOver() == TRUE)
    return;

  ApplyCurseOfDarknessDamage();
}

static void ActivateCurseOfDarknessZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(9);
    gCardEffectTextData.cardId = CURSE_OF_DARKNESS;
    ActivateCardEffectText();
  }
}

void TryActivateCurseOfDarknessOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != CURSE_OF_DARKNESS || zone->isFaceUp != FALSE)
      continue;

    ActivateCurseOfDarknessZone(zone);
  }
}
