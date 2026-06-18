#include "global.h"
#include "common-chax.h"
#include "amazoness_tiger.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

extern void UpdateDuelGfxExceptField(void);

#define AMAZONESS_TIGER_BASE_ATK 1100
#define AMAZONESS_TIGER_ATK_PER_AMAZONESS 400

static u8 IsAmazonessZone(struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE && Duel_IsAmazonessCard(zone->id);
}

static u8 CountAmazonessOnFixedRow(u8 fixedRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsAmazonessZone(gFixedZones[fixedRow][col]))
      count++;
  }

  return count;
}

// ponytail: normal hand summon copies isFaceUp=0; attack-position monsters still count
static u8 IsTigerUniquenessActive(struct DuelCard *zone)
{
  return zone != NULL && zone->id == AMAZONESS_TIGER
      && (zone->isFaceUp || !zone->isDefending);
}

static struct DuelCard *FindFaceUpTigerOnFixedRow(u8 fixedRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == AMAZONESS_TIGER && zone->isFaceUp)
      return zone;
  }

  return NULL;
}

static struct DuelCard *FindActiveTigerOnFixedRow(u8 fixedRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (IsTigerUniquenessActive(zone))
      return zone;
  }

  return NULL;
}

static u8 RowHasOtherActiveTiger(u8 fixedRow, struct DuelCard *exceptZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == exceptZone || !IsTigerUniquenessActive(zone))
      continue;

    return TRUE;
  }

  return FALSE;
}

static void EnforceUniqueTigerOnRow(u8 fixedRow, struct DuelCard *keepZone, u8 showActivationText)
{
  u8 col;
  u8 graveyardDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  u8 destroyed = FALSE;

  if (!RowHasOtherActiveTiger(fixedRow, keepZone))
    return;

  if (showActivationText)
    Duel_ShowEffectTextTyped(AMAZONESS_TIGER, 2);

  if (IsDuelOver())
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == keepZone || !IsTigerUniquenessActive(zone))
      continue;

    Duel_DestroyZone(zone, graveyardDuelist, FALSE);
    destroyed = TRUE;
  }

  if (destroyed)
    UpdateDuelGfxExceptField();
}

u8 AmazonessTiger_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 count;

  if (zone == NULL || zone->id != AMAZONESS_TIGER)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  count = CountAmazonessOnFixedRow(fixedRow);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(
      zone->id,
      Duel_StatFromCount(count, AMAZONESS_TIGER_ATK_PER_AMAZONESS, AMAZONESS_TIGER_BASE_ATK),
      gCardInfo.def);
  return TRUE;
}

u8 AmazonessTiger_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!IsAmazonessZone(zone) || zone->id == AMAZONESS_TIGER || !zone->isFaceUp)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return FindFaceUpTigerOnFixedRow(fixedRow) == NULL;
}

void TryAmazonessTigerOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!IsTigerUniquenessActive(zone))
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  EnforceUniqueTigerOnRow(fixedRow, zone, TRUE);
}

void AmazonessTiger_EnforceUniquenessOnField(void)
{
  u8 fixedRow;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    struct DuelCard *keeper = FindActiveTigerOnFixedRow(fixedRow);

    if (keeper != NULL)
      EnforceUniqueTigerOnRow(fixedRow, keeper, FALSE);
  }
}

void AmazonessTiger_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = AMAZONESS_TIGER;
  AmazonessTiger_ApplyDynamicZoneStats(&zone);
}
