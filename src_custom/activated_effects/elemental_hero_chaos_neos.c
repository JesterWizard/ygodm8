#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 CountCoinHeads(u8 flips)
{
  u8 i;
  u8 heads = 0;

  for (i = 0; i < flips; i++) {
    if (RandRangeU8(0, 1) == 1)
      heads++;
  }

  return heads;
}

static u8 IsOppMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppHasMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppMonster(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void DestroyUpToNOppMonsters(u8 max)
{
  u8 destroyed = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < max; col++) {
    struct DuelCard *zone;

    if (!IsOppMonster(INACTIVE_DUELIST_MONSTER_ROW, col))
      continue;

    zone = gFixedZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;

    destroyed++;
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateELEMENTAL_HERO_CHAOS_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_CHAOS_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_CHAOS_NEOS)
    return FALSE;

  /* ponytail: EP shuffle/Set-all + exact 3H/2H/1H/0H branch table FALSE.
   * Ceiling: OPT 3 coin → destroy heads-count opp monsters. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasMonster();
}

void ActivateELEMENTAL_HERO_CHAOS_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 heads;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_CHAOS_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  heads = CountCoinHeads(3);
  if (heads > 0)
    DestroyUpToNOppMonsters(heads);

  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
