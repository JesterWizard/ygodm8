#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

#define MAGICAL_MARIONETTE_COUNTER_COST 2

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 graveyardDuelist;

  if (!IsValidDestroyTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (self->unk4 < MAGICAL_MARIONETTE_COUNTER_COST)
    return;

  self->unk4 = (u8)(self->unk4 - MAGICAL_MARIONETTE_COUNTER_COST);

  if (fixedRow == ACTIVE_DUELIST_MONSTER_ROW || fixedRow == ACTIVE_DUELIST_BACKROW)
    graveyardDuelist = ACTIVE_DUELIST;
  else
    graveyardDuelist = INACTIVE_DUELIST;

  if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMAGICAL_MARIONETTE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAGICAL_MARIONETTE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAGICAL_MARIONETTE)
    return FALSE;

  /* Spell Counter on resolve via TryIncrementSpellCountersOnSpellResolve;
   * +200 ATK/counter via ApplyMagicalMarionetteStatBoostToCardInfo.
   * Ceiling: OPT remove 2 unk4 counters → destroy 1 monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->unk4 < MAGICAL_MARIONETTE_COUNTER_COST)
    return FALSE;

  return FieldHasDestroyTarget();
}

void ActivateMAGICAL_MARIONETTEEffect(void)
{
  Duel_ShowEffectTextTyped(MAGICAL_MARIONETTE, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidDestroyTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

#define MAGICAL_MARIONETTE_COUNTER_ATK 200

void ApplyMagicalMarionetteStatBoostToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != MAGICAL_MARIONETTE || zone->unk4 == 0)
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk
      + (u32)zone->unk4 * MAGICAL_MARIONETTE_COUNTER_ATK);
}
