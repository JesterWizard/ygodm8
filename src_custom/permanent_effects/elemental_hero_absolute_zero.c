#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "mini_card.h"

#define ABSOLUTE_ZERO_BASE_ATK 2500
#define ABSOLUTE_ZERO_ATK_PER_WATER 500

static u8 ZoneCountsForAbsoluteZeroAtk(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (zone->id == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

static u8 CountWaterMonstersForAbsoluteZero(void)
{
  return Duel_CountFixedMonstersMatching(ZoneCountsForAbsoluteZeroAtk);
}

static u16 AbsoluteZeroCurrentAtk(void)
{
  return Duel_StatFromCount(
      CountWaterMonstersForAbsoluteZero(),
      ABSOLUTE_ZERO_ATK_PER_WATER,
      ABSOLUTE_ZERO_BASE_ATK);
}

u8 ElementalHeroAbsoluteZero_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 def;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_ABSOLUTE_ZERO)
    return FALSE;

  SetCardInfo(zone->id);
  def = gCardInfo.def;
  Duel_WriteCardInfoStats(zone->id, AbsoluteZeroCurrentAtk(), def);
  return TRUE;
}

static struct DuelCard *FindActiveAbsoluteZero(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == ELEMENTAL_HERO_ABSOLUTE_ZERO && IsCardFaceUp(zone))
        return zone;
    }
  }

  return NULL;
}

u8 ElementalHeroAbsoluteZero_IsActiveOnField(void)
{
  return FindActiveAbsoluteZero() != NULL;
}

void ElementalHeroAbsoluteZero_RefreshStatsIfActive(void)
{
  if (ElementalHeroAbsoluteZero_IsActiveOnField())
    RefreshFieldMonsterStatOverlays();
}

void TryElementalHeroAbsoluteZeroOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  ElementalHeroAbsoluteZero_RefreshStatsIfActive();
}

void MarkAbsoluteZeroHandGraveyardClear(void)
{
  gAbsoluteZeroHandGyClearPending = TRUE;
}

void MarkAbsoluteZeroHandSummonCleanup(void)
{
  gAbsoluteZeroHandSummonCleanupPending = TRUE;
}

void ElementalHeroAbsoluteZero_BeginSuppressLeave(void)
{
  gAbsoluteZeroSuppressLeave = TRUE;
}

void ElementalHeroAbsoluteZero_EndSuppressLeave(void)
{
  gAbsoluteZeroSuppressLeave = FALSE;
}

void ElementalHeroAbsoluteZero_ResetPendingState(void)
{
  gAbsoluteZeroHandGyClearPending = FALSE;
  gAbsoluteZeroHandSummonCleanupPending = FALSE;
  gAbsoluteZeroSuppressLeave = FALSE;
}

static u8 ConsumeAbsoluteZeroHandGraveyardClear(void)
{
  if (!gAbsoluteZeroHandGyClearPending)
    return FALSE;

  gAbsoluteZeroHandGyClearPending = FALSE;
  return TRUE;
}

static u8 ConsumeAbsoluteZeroHandSummonCleanup(void)
{
  if (!gAbsoluteZeroHandSummonCleanupPending)
    return FALSE;

  gAbsoluteZeroHandSummonCleanupPending = FALSE;
  return TRUE;
}

static u8 ShouldTriggerAbsoluteZeroLeave(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL)
    return FALSE;

  if (gAbsoluteZeroSuppressLeave)
    return FALSE;

  if (Duel_ZoneIsHandSlot(zone)) {
    if (ConsumeAbsoluteZeroHandSummonCleanup()) {
      gAbsoluteZeroHandGyClearPending = FALSE;
      return FALSE;
    }

    return ConsumeAbsoluteZeroHandGraveyardClear()
        && zone->id == ELEMENTAL_HERO_ABSOLUTE_ZERO;
  }

  if (zone->id != ELEMENTAL_HERO_ABSOLUTE_ZERO)
    return FALSE;

  return Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col);
}

void ElementalHeroAbsoluteZero_OnZoneCleared(const struct DuelCard *zone)
{
  u8 opponentFixedRow;
  u8 opponentTurnRow;

  if (!ShouldTriggerAbsoluteZeroLeave(zone))
    return;

  ActivatePermanentEffectCardText(ELEMENTAL_HERO_ABSOLUTE_ZERO);

  if (IsDuelOver() == TRUE)
    return;

  opponentFixedRow = Duel_OpponentMonsterRowForZone((struct DuelCard *)zone);
  opponentTurnRow = Duel_FixedMonsterRowToTurnMonsterRow(opponentFixedRow);

  if (Duel_DestroyAllMonstersMatching(opponentTurnRow, NULL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

#if !defined(__GNUC__)
#error Elemental HERO Absolute Zero stat hook self-check requires GCC
#elif __GNUC__
void ElementalHeroAbsoluteZero_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_ABSOLUTE_ZERO;
  ElementalHeroAbsoluteZero_ApplyDynamicZoneStats(&zone);
}
#endif
