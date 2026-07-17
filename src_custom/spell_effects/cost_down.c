#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cost_down.h"
#include "duel_helpers.h"
#include "six_card_hand.h"
#include "spell_effects.h"

static u8 IsMonsterCardId(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].type < TYPE_SPELL;
}

static u8 IsCardInCostDownHandSlot(u8 handSlot, u16 cardId)
{
  struct DuelCard *zone;
  u8 maxSlot = IsSixCardHandEnabled() ? HAND_SLOT_EXTRA : (MAX_ZONES_IN_ROW - 1);

  if (handSlot > maxSlot || cardId == CARD_NONE)
    return FALSE;

  if (gCostDownTargetDuelist == DUEL_PLAYER)
    zone = SixCardHand_GetPlayerHandZone(handSlot);
  else
    zone = SixCardHand_GetFixed(gCostDownTargetDuelist, handSlot);

  return zone != NULL && zone->id == cardId;
}

static u8 IsMonsterInCostDownHand(u16 cardId)
{
  u8 i;
  u8 maxSlot = IsSixCardHandEnabled() ? HAND_SLOT_EXTRA : (MAX_ZONES_IN_ROW - 1);

  if (!gCostDownActive || !IsMonsterCardId(cardId))
    return FALSE;

  for (i = 0; i <= maxSlot; i++) {
    if (IsCardInCostDownHandSlot(i, cardId))
      return TRUE;
  }

  return FALSE;
}

void EnableCostDownForTurn(void)
{
  gCostDownActive = 1;
  gCostDownTargetDuelist = WhoseTurn();
}

void ClearCostDown(void)
{
  gCostDownActive = 0;
  gCostDownTargetDuelist = DUEL_PLAYER;
}

u8 GetCostDownAdjustedLevel(u16 cardId, u8 baseLevel)
{
  if (cardId < NUM_TOTAL_CARDS)
    baseLevel = gCardData_NEW[cardId].level;

  if (!gCostDownActive || !IsMonsterCardId(cardId))
    return baseLevel;

  if (baseLevel <= COST_DOWN_LEVEL_REDUCTION)
    return 1;

  return baseLevel - COST_DOWN_LEVEL_REDUCTION;
}

u8 ShouldApplyCostDownLevelForTribute(u16 cardId)
{
  return gCostDownActive != 0 && IsMonsterInCostDownHand(cardId);
}

u8 ShouldApplyCostDownForHandSlot(u8 handSlot, u16 cardId)
{
  return gCostDownActive != 0 && IsMonsterCardId(cardId)
      && IsCardInCostDownHandSlot(handSlot, cardId);
}

APPEND_TEXT void EffectCostDown(void)
{
  EnableCostDownForTurn();
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(COST_DOWN);
}
