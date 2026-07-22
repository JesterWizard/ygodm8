#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
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

static void DestroyAllSpellTraps(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;

      if (!IsSpellTrapZone(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (zone == NULL)
        continue;

      if (Duel_DestroyZone(zone, GraveyardDuelistForBackrow(row), FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateELEMENTAL_HERO_STORM_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_STORM_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_STORM_NEOS)
    return FALSE;

  /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT destroy all
   * S/T on field. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasSpellTrap();
}

void ActivateELEMENTAL_HERO_STORM_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_STORM_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  DestroyAllSpellTraps();
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
