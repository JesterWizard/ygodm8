#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cost_down.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 IsMonsterCardId(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].type < TYPE_SPELL;
}

static u8 IsCardInCostDownHandSlot(u8 handSlot, u16 cardId)
{
  if (handSlot >= MAX_ZONES_IN_ROW || cardId == CARD_NONE)
    return FALSE;

  if (gCostDownTargetDuelist == DUEL_PLAYER)
    return gFixedZones[PLAYER_HAND][handSlot]->id == cardId;

  return gDuel.hands[gCostDownTargetDuelist][handSlot].id == cardId;
}

static u8 IsMonsterInCostDownHand(u16 cardId)
{
  u8 i;

  if (!gCostDownActive || !IsMonsterCardId(cardId))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
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
