#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "solar_ray.h"

#define SOLAR_RAY_DAMAGE_PER_MONSTER 600

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);
u32 NumFaceUpMatchingAttributeInRow(u8, u8);

static void ApplySolarRayDamage(u8 lightMonsterCount)
{
  u16 damage;

  if (lightMonsterCount == 0)
    return;

  damage = (u16)lightMonsterCount * SOLAR_RAY_DAMAGE_PER_MONSTER;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(damage);
  else
    SetOpponentLifePointsToSubtract(damage);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void ActivateSolarRayZone(struct DuelCard *zone, u8 lightMonsterCount)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SOLAR_RAY;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  ApplySolarRayDamage(lightMonsterCount);
}

void TryActivateSolarRayOnOpponentTurnStart(void)
{
  u8 i;
  u8 lightMonsterCount;
  struct DuelCard *zone;

  lightMonsterCount = NumFaceUpMatchingAttributeInRow(INACTIVE_DUELIST_MONSTER_ROW, ATTRIBUTE_LIGHT);
  if (lightMonsterCount == 0)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != SOLAR_RAY || zone->isFaceUp != FALSE)
      continue;

    ActivateSolarRayZone(zone, lightMonsterCount);
    if (IsDuelOver() == TRUE)
      return;
  }
}
