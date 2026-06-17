#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "curse_of_darkness.h"

#define CURSE_OF_DARKNESS_DAMAGE 1000

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

void TryApplyCurseOfDarknessSpellDamage(void)
{
  if (gHideEffectText)
    return;

  if (!IsCurseOfDarknessActiveOnField())
    return;

  Duel_ShowEffectTextTyped(CURSE_OF_DARKNESS, 3);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ChangeLp(ACTIVE_DUELIST, -CURSE_OF_DARKNESS_DAMAGE, FALSE);
}

static void ActivateCurseOfDarknessZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(CURSE_OF_DARKNESS, 9);
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
