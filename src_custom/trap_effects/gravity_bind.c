#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gravity_bind.h"

#define GRAVITY_BIND_MIN_BLOCKED_LEVEL 4

static u8 ZoneIsFaceUpGravityBind(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == GRAVITY_BIND && zone->isFaceUp == TRUE;
}

static u8 MonsterLevelIsBlockedByGravityBind(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= GRAVITY_BIND_MIN_BLOCKED_LEVEL;
}

u8 IsActivatedGravityBindZone(const struct DuelCard *zone)
{
  return ZoneIsFaceUpGravityBind(zone);
}

u8 IsGravityBindActiveOnField(void)
{
  u8 row;
  u8 i;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (ZoneIsFaceUpGravityBind(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 GravityBind_ShouldActivateTrapOnAttack(const struct DuelCard *trapZone, u16 attackerCardId)
{
  if (trapZone == NULL || trapZone->id != GRAVITY_BIND || trapZone->isFaceUp)
    return FALSE;

  if (GetTypeGroup(attackerCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return MonsterLevelIsBlockedByGravityBind(attackerCardId);
}

u8 GravityBind_CanMonsterAttack(u16 cardId)
{
  u8 i;

  if (!MonsterLevelIsBlockedByGravityBind(cardId))
    return TRUE;

  if (IsGravityBindActiveOnField())
    return FALSE;

  // ponytail: face-down GB still blocks the declare; AI sim restore keeps it face-down every trial
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (GravityBind_ShouldActivateTrapOnAttack(
            gTurnZones[INACTIVE_DUELIST_BACKROW][i], cardId))
      return FALSE;
  }

  return TRUE;
}

APPEND_TEXT void EffectGravityBind(void)
{
  struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ActivateContinuousZone(zone);

  Duel_ShowTrapResponseText(GRAVITY_BIND, gTrapEffectData.originCardId);
}
