#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "royal_decree.h"
#include "wall_of_revealing_light.h"

u16 gWallOfRevealingLightAttackThreshold;

static u8 ZoneIsFaceUpWallOfRevealingLight(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == WALL_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE;
}

static u8 WallControllerForBackrowRow(u8 fixedRow)
{
  return fixedRow == OPPONENT_BACKROW ? DUEL_OPPONENT : DUEL_PLAYER;
}

static u8 AttackerIsOpponentOfWallController(const struct DuelCard *zone, u8 wallController)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  return Duel_FixedDuelistForMonsterRow(fixedRow) != wallController;
}

static u8 WallAffectsAttacker(const struct DuelCard *zone, u16 *threshold, u8 *wallController)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *wall = gFixedZones[row][col];

      if (!ZoneIsFaceUpWallOfRevealingLight(wall))
        continue;
      if (IsRoyalDecreeNegatingTrap(WALL_OF_REVEALING_LIGHT))
        continue;

      *wallController = WallControllerForBackrowRow(row);
      if (!AttackerIsOpponentOfWallController(zone, *wallController))
        return FALSE;

      if (gWallOfRevealingLightAttackThreshold == 0)
        return FALSE;

      *threshold = gWallOfRevealingLightAttackThreshold;
      return TRUE;
    }
  }

  return FALSE;
}

void WallOfRevealingLight_ClearThreshold(void)
{
  gWallOfRevealingLightAttackThreshold = 0;
}

u8 IsActivatedWallOfRevealingLightZone(const struct DuelCard *zone)
{
  return ZoneIsFaceUpWallOfRevealingLight(zone);
}

u8 IsWallOfRevealingLightActiveOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (ZoneIsFaceUpWallOfRevealingLight(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 WallOfRevealingLight_ShouldActivateTrapOnAttack(const struct DuelCard *trapZone, u16 attackerCardId)
{
  if (trapZone == NULL || trapZone->id != WALL_OF_REVEALING_LIGHT || trapZone->isFaceUp)
    return FALSE;

  if (GetTypeGroup(attackerCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return TRUE;
}

u8 WallOfRevealingLight_CanMonsterAttack(const struct DuelCard *zone)
{
  u16 threshold;
  u8 wallController;

  if (!WallAffectsAttacker(zone, &threshold, &wallController))
    return TRUE;

  return Duel_GetZoneFinalAtk((struct DuelCard *)zone) > threshold;
}

APPEND_TEXT void EffectWallOfRevealingLight(void)
{
  struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  u16 cost = gDuelLifePoints[INACTIVE_DUELIST] / 2;

  gWallOfRevealingLightAttackThreshold = cost;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)cost, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowTrapResponseText(WALL_OF_REVEALING_LIGHT, gTrapEffectData.originCardId);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void WallOfRevealingLight_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = WALL_OF_REVEALING_LIGHT;
  zone.isFaceUp = TRUE;
  if (!IsActivatedWallOfRevealingLightZone(&zone))
    __builtin_trap();
}
#endif
