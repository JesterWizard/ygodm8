#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "level_limit_area_b.h"
#include "spell_effects.h"

static u8 MonsterLevelIsRestrictedByLevelLimitAreaB(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= LEVEL_LIMIT_AREA_B_MIN_RESTRICTED_LEVEL;
}

u8 IsActivatedLevelLimitAreaBZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == LEVEL_LIMIT_AREA_B && zone->isFaceUp == TRUE;
}

u8 IsLevelLimitAreaBActiveOnField(void)
{
  if (IsImperialOrderNegatingSpell(LEVEL_LIMIT_AREA_B))
    return FALSE;

  return Duel_IsBackrowCardOnField(LEVEL_LIMIT_AREA_B, TRUE);
}

u8 LevelLimitAreaB_CannotUseAttackPosition(u16 cardId)
{
  if (!IsLevelLimitAreaBActiveOnField())
    return FALSE;

  return MonsterLevelIsRestrictedByLevelLimitAreaB(cardId);
}

u8 LevelLimitAreaB_CanMonsterAttack(const struct DuelCard *zone)
{
  if (!IsLevelLimitAreaBActiveOnField())
    return TRUE;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  if (!MonsterLevelIsRestrictedByLevelLimitAreaB(zone->id))
    return TRUE;

  // Lv4+ cannot declare an attack while LLAB is active.
  return FALSE;
}

static void EnforceDefensePosition(struct DuelCard *zone, u8 faceUpOnly)
{
  if (!IsLevelLimitAreaBActiveOnField())
    return;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (faceUpOnly && !zone->isFaceUp)
    return;

  if (zone->isDefending)
    return;

  if (!MonsterLevelIsRestrictedByLevelLimitAreaB(zone->id))
    return;

  zone->isDefending = TRUE;
}

void LevelLimitAreaB_EnforceOnZone(struct DuelCard *zone)
{
  EnforceDefensePosition(zone, TRUE);
}

void LevelLimitAreaB_EnforceOnSummon(struct DuelCard *zone)
{
  EnforceDefensePosition(zone, FALSE);
}

static void EnforceLevelLimitAreaBOnFixedRow(u8 fixedRow)
{
  u8 col;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    LevelLimitAreaB_EnforceOnZone(gFixedZones[fixedRow][col]);
}

void LevelLimitAreaB_EnforceOnField(void)
{
  if (!IsLevelLimitAreaBActiveOnField())
    return;

  EnforceLevelLimitAreaBOnFixedRow(OPPONENT_MONSTER_ROW);
  EnforceLevelLimitAreaBOnFixedRow(PLAYER_MONSTER_ROW);
}

void LevelLimitAreaB_CheckAfterFieldChange(void)
{
  LevelLimitAreaB_EnforceOnField();
}

void TryLevelLimitAreaBOnMonsterPlacement(struct DuelCard *zone)
{
  LevelLimitAreaB_EnforceOnSummon(zone);
}

APPEND_TEXT void EffectLevelLimitAreaB(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LEVEL_LIMIT_AREA_B);

  if (IsDuelOver() == TRUE)
    return;

  LevelLimitAreaB_EnforceOnField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LevelLimitAreaB_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = LEVEL_LIMIT_AREA_B;
  zone.isFaceUp = TRUE;
  if (!IsActivatedLevelLimitAreaBZone(&zone))
    __builtin_trap();
}
#endif
