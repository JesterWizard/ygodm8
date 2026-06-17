#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mask_of_restrict.h"

void UpdateDuelGfxExceptField(void);

static u8 ZoneIsFaceUpMaskOfRestrict(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MASK_OF_RESTRICT && zone->isFaceUp == TRUE;
}

static u8 ZoneIsSetMaskOfRestrict(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MASK_OF_RESTRICT && zone->isFaceUp == FALSE;
}

u8 IsActivatedMaskOfRestrictZone(const struct DuelCard *zone)
{
  return ZoneIsFaceUpMaskOfRestrict(zone);
}

u8 IsMaskOfRestrictActiveOnField(void)
{
  u8 row;
  u8 i;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (ZoneIsFaceUpMaskOfRestrict(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

static struct DuelCard *FindSetMaskOfRestrictOnField(void)
{
  u8 row;
  u8 i;
  struct DuelCard *zone;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      zone = gFixedZones[row][i];
      if (ZoneIsSetMaskOfRestrict(zone))
        return zone;
    }
  }

  return NULL;
}

u8 MaskOfRestrictOnField(void)
{
  return IsMaskOfRestrictActiveOnField() || FindSetMaskOfRestrictOnField() != NULL;
}

static void ActivateMaskOfRestrictZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(MASK_OF_RESTRICT, 9);
}

u8 TryBlockTributeWithMaskOfRestrict(void)
{
  struct DuelCard *setZone;

  if (!MaskOfRestrictOnField())
    return FALSE;

  setZone = FindSetMaskOfRestrictOnField();
  if (setZone != NULL) {
    ActivateMaskOfRestrictZone(setZone);
    UpdateDuelGfxExceptField();
  }

  return TRUE;
}
