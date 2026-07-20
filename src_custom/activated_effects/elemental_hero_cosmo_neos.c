#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

  /* ponytail: activation lock / End Phase field wipe FALSE.
   * Ceiling: OPT destroy all opp Spell/Trap. */
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

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
