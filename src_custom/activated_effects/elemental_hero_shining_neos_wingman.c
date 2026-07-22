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

extern const CardData gCardData_NEW[];

static u8 CountDifferentAttributesOnField(void)
{
  u8 seen[16];
  u8 row;
  u8 col;
  u8 i;
  u8 count = 0;

  for (i = 0; i < 16; i++)
    seen[i] = FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];
      u8 attr;

      if (zone == NULL || zone->id == CARD_NONE
          || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      SetCardInfo(zone->id);
      attr = gCardInfo.attribute;
      if (attr >= 16 || seen[attr])
        continue;

      seen[attr] = TRUE;
      count++;
    }
  }

  return count;
}

static u8 IsOppFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppFieldHasCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CountOppFieldCards(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col))
        count++;
    }
  }

  return count;
}

static u8 DestroyUpToNOppCards(u8 max)
{
  u8 destroyed = 0;
  u8 row;
  u8 col;

  while (destroyed < max) {
    u8 bestRow = 0xFF;
    u8 bestCol = 0xFF;
    u16 bestScore = 0;

    for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
      for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
        struct DuelCard *zone;
        u16 score;

        if (!IsOppFieldCard(row, col))
          continue;

        zone = gFixedZones[row][col];
        if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
          score = gCardData_NEW[zone->id].atk + 100;
        else
          score = 50;

        if (bestRow == 0xFF || score > bestScore) {
          bestScore = score;
          bestRow = row;
          bestCol = col;
        }
      }
    }

    if (bestRow == 0xFF)
      break;

    if (Duel_DestroyZone(gFixedZones[bestRow][bestCol], INACTIVE_DUELIST, FALSE)
        == DUEL_ACTION_DUEL_OVER)
      return destroyed;

    destroyed++;
  }

  return destroyed;
}

unsigned char CanActivateELEMENTAL_HERO_SHINING_NEOS_WINGMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_SHINING_NEOS_WINGMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_SHINING_NEOS_WINGMAN)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountDifferentAttributesOnField() > 0 && OppFieldHasCard();
}

void ActivateELEMENTAL_HERO_SHINING_NEOS_WINGMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 max;
  u8 oppCount;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_SHINING_NEOS_WINGMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  max = CountDifferentAttributesOnField();
  oppCount = CountOppFieldCards();
  if (max > oppCount)
    max = oppCount;

  if (max == 0)
    return;

  /* Printed remainder omitted by this ruleset. */
  if (DestroyUpToNOppCards(max) == 0)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
