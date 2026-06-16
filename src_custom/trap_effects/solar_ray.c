#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "duel_helpers.h"
#include "solar_ray.h"

#define SOLAR_RAY_DAMAGE_PER_MONSTER 600

u32 NumFaceUpMatchingAttributeInRow(u8, u8);

static void ActivateSolarRayZone(struct DuelCard *zone, u8 lightMonsterCount)
{
  u16 damage;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(SOLAR_RAY, 3);

  if (IsDuelOver() == TRUE)
    return;

  if (lightMonsterCount == 0)
    return;

  damage = (u16)lightMonsterCount * SOLAR_RAY_DAMAGE_PER_MONSTER;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, FALSE);
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
