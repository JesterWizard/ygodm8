#include "global.h"
#include "common-chax.h"
#include "chimeratech_rampage_dragon.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 typeGroup;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 FieldHasSpellTrap(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsSpellTrapZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 GraveyardDuelistForBackrow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static void DestroyUpToSpellTraps(u8 maxCount)
{
  u8 destroyed = 0;
  u8 row;
  u8 col;

  if (maxCount == 0)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW && destroyed < maxCount; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < maxCount; col++) {
      struct DuelCard *zone;

      if (!IsSpellTrapZone(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (zone == NULL)
        continue;

      if (Duel_DestroyZone(zone, GraveyardDuelistForBackrow(row), FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed++;
    }
  }
}

unsigned char CanActivateCHIMERATECH_RAMPAGE_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CHIMERATECH_RAMPAGE_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CHIMERATECH_RAMPAGE_DRAGON)
    return FALSE;

  /* On-Fusion destroy via ChimeratechRampageDragon_OnFusionSummoned.
   * OPT destroy up to 2 S/T on field below. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasSpellTrap();
}

void ActivateCHIMERATECH_RAMPAGE_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CHIMERATECH_RAMPAGE_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  DestroyUpToSpellTraps(2);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void ChimeratechRampageDragon_OnFusionSummoned(struct DuelCard *zone, u8 materialCount)
{
  if (zone == NULL || zone->id != CHIMERATECH_RAMPAGE_DRAGON)
    return;

  if (materialCount < 2)
    materialCount = 2;
  if (materialCount > FUSION_MAX_MATERIALS)
    materialCount = FUSION_MAX_MATERIALS;

  Duel_ShowEffectTextTyped(CHIMERATECH_RAMPAGE_DRAGON, 2);
  if (IsDuelOver() == TRUE)
    return;

  DestroyUpToSpellTraps(materialCount);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
