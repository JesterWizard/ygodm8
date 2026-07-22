#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define COSMO_NEOS_EP_PENDING 1

static u8 IsOppSpellTrap(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OppHasSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrap(INACTIVE_DUELIST_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void DestroyAllOppSpellTraps(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!IsOppSpellTrap(INACTIVE_DUELIST_BACKROW, col))
      continue;

    zone = gFixedZones[INACTIVE_DUELIST_BACKROW][col];
    if (zone == NULL)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateELEMENTAL_HERO_COSMO_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_COSMO_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_COSMO_NEOS)
    return FALSE;

  /* EP field wipe via TryApplyElementalHeroCosmoNeosEndPhase.
   * OPT destroy all opp Spell/Trap. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasSpellTrap();
}

void ActivateELEMENTAL_HERO_COSMO_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_COSMO_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  DestroyAllOppSpellTraps();

  if (IsDuelOver() == TRUE)
    return;

  self->unkTwo = COSMO_NEOS_EP_PENDING;
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void TryApplyElementalHeroCosmoNeosEndPhase(void)
{
  u8 fixedRow;
  u8 col;
  u8 pending = FALSE;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone != NULL && zone->id == ELEMENTAL_HERO_COSMO_NEOS
          && zone->unkTwo == COSMO_NEOS_EP_PENDING)
        pending = TRUE;
    }
  }

  if (!pending)
    return;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_COSMO_NEOS, 8);

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_BACKROW; fixedRow++) {
    u8 ownerFixed = (fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW)
        ? DUEL_OPPONENT
        : DUEL_PLAYER;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if (Duel_DestroyZone(zone, Duel_TurnDuelistForFixedDuelist(ownerFixed), FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return;

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
}
