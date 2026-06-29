#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_thunder_giant.h"
#include "god_card.h"
#include "monster_effect_usage.h"

extern void UpdateDuelGfxExceptField(void);
extern void CheckWinConditionExodia(void);
extern void TryActivatingPermanentEffects(void);

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static struct DuelCard *ThunderGiantSourceZone(void)
{
  return gTurnZones[gMonEffect.row][gMonEffect.zone];
}

static u16 ThunderGiantAttackValue(void)
{
  return Duel_GetZoneFinalAtk(ThunderGiantSourceZone());
}

static u8 TargetOriginalAtkBelowThunderGiant(struct DuelCard *zone)
{
  return gCardData_NEW[zone->id].atk < ThunderGiantAttackValue();
}

static u8 GraveyardDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!IsFaceUpMonsterZone(zone))
    return FALSE;

  return TargetOriginalAtkBelowThunderGiant(zone);
}

static u8 FindFirstTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void DestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (Duel_DestroyZone(zone, GraveyardDuelistForMonsterFixedRow(fixedRow), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidTarget(fixedRow, fixedCol))
    return;

  DestroyTarget(fixedRow, fixedCol);
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = gCardData_NEW[zone->id].atk;
      if (bestRow == 0xFF || atk > bestAtk) {
        bestRow = row;
        bestCol = col;
        bestAtk = atk;
      }
    }
  }

  if (bestRow == 0xFF)
    return FALSE;

  *outRow = bestRow;
  *outCol = bestCol;
  return TRUE;
}

static u8 DiscardCostCard(void)
{
  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  return IsDuelOver() != TRUE;
}

static void BeginDestroyTargeting(void)
{
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char CanActivateElementalHeroThunderGiant(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != ELEMENTAL_HERO_THUNDER_GIANT)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return FindFirstTarget(&unusedRow, &unusedCol);
}

void ActivateElementalHeroThunderGiantEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_THUNDER_GIANT, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (!DiscardCostCard())
    return;

  BeginDestroyTargeting();
}
