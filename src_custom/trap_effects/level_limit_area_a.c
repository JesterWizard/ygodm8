#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "level_limit_area_a.h"

static u8 MonsterLevelIsForcedByLevelLimitAreaA(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= LEVEL_LIMIT_AREA_A_MAX_FORCED_LEVEL;
}

u8 IsActivatedLevelLimitAreaAZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == LEVEL_LIMIT_AREA_A && zone->isFaceUp == TRUE;
}

u8 IsLevelLimitAreaAActiveOnField(void)
{
  return Duel_IsBackrowCardOnField(LEVEL_LIMIT_AREA_A, TRUE);
}

u8 LevelLimitAreaA_CannotUseDefensePosition(u16 cardId)
{
  if (!IsLevelLimitAreaAActiveOnField())
    return FALSE;

  return MonsterLevelIsForcedByLevelLimitAreaA(cardId);
}

static void EnforceAttackPosition(struct DuelCard *zone, u8 faceUpOnly)
{
  if (!IsLevelLimitAreaAActiveOnField())
    return;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (faceUpOnly && !zone->isFaceUp)
    return;

  if (!zone->isDefending)
    return;

  if (!MonsterLevelIsForcedByLevelLimitAreaA(zone->id))
    return;

  zone->isDefending = FALSE;
}

void LevelLimitAreaA_ForceOnZone(struct DuelCard *zone)
{
  EnforceAttackPosition(zone, TRUE);
}

void LevelLimitAreaA_ForceOnSummon(struct DuelCard *zone)
{
  EnforceAttackPosition(zone, FALSE);
}

static void EnforceLevelLimitAreaAOnFixedRow(u8 fixedRow)
{
  u8 col;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    LevelLimitAreaA_ForceOnZone(gFixedZones[fixedRow][col]);
}

void LevelLimitAreaA_ForceOnField(void)
{
  if (!IsLevelLimitAreaAActiveOnField())
    return;

  EnforceLevelLimitAreaAOnFixedRow(OPPONENT_MONSTER_ROW);
  EnforceLevelLimitAreaAOnFixedRow(PLAYER_MONSTER_ROW);
}

void LevelLimitAreaA_CheckAfterFieldChange(void)
{
  LevelLimitAreaA_ForceOnField();
}

void TryLevelLimitAreaAOnMonsterPlacement(struct DuelCard *zone)
{
  LevelLimitAreaA_ForceOnSummon(zone);
}

void TryActivateLevelLimitAreaAOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != LEVEL_LIMIT_AREA_A || zone->isFaceUp != FALSE)
      continue;

    Duel_ActivateContinuousZone(zone);
    Duel_ShowEffectText(LEVEL_LIMIT_AREA_A);

    if (IsDuelOver() == TRUE)
      return;

    LevelLimitAreaA_ForceOnField();
  }
}

APPEND_TEXT void EffectLevelLimitAreaA(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LEVEL_LIMIT_AREA_A);

  if (IsDuelOver() == TRUE)
    return;

  LevelLimitAreaA_ForceOnField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LevelLimitAreaA_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = LEVEL_LIMIT_AREA_A;
  zone.isFaceUp = TRUE;
  if (!IsActivatedLevelLimitAreaAZone(&zone))
    __builtin_trap();
}
#endif
