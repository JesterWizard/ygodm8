#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "imperial_order.h"

void ActivateTrapEffect(u16 lp);

#define IMPERIAL_ORDER_LP_COST 700

void EffectImperialOrder(void)
{
  struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = IMPERIAL_ORDER;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}

void TryActivateImperialOrderOnSpellChain(void)
{
  u8 i;
  struct DuelCard *zone;

  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_SPELL)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone == NULL || zone->id != IMPERIAL_ORDER || zone->isFaceUp)
      continue;

    gTrapEffectData.trapZoneCol = i;
    gTrapEffectData.trapCardId = TRAP_IMPERIAL_ORDER;
    ActivateTrapEffect(0);
    return;
  }
}

static struct DuelCard *FindFaceUpImperialOrderOnBackrow(u8 row)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[row][i];
    if (zone != NULL && zone->id == IMPERIAL_ORDER && zone->isFaceUp)
      return zone;
  }

  return NULL;
}

u8 IsImperialOrderActiveOnField(void)
{
  if (FindFaceUpImperialOrderOnBackrow(PLAYER_BACKROW) != NULL)
    return TRUE;

  return FindFaceUpImperialOrderOnBackrow(OPPONENT_BACKROW) != NULL;
}

u8 IsImperialOrderNegatingSpell(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return IsImperialOrderActiveOnField()
      && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 ActiveDuelistCanPayImperialOrderCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= IMPERIAL_ORDER_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= IMPERIAL_ORDER_LP_COST;
}

static void ApplyImperialOrderLpCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(IMPERIAL_ORDER_LP_COST);
  else
    SetOpponentLifePointsToSubtract(IMPERIAL_ORDER_LP_COST);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

unsigned char ShouldActivateImperialOrderUpkeep(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;
  if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[ACTIVE_DUELIST_BACKROW], IMPERIAL_ORDER))
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->id == IMPERIAL_ORDER && zone->isFaceUp == TRUE;
}

void ActivateImperialOrderUpkeep(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (ActiveDuelistCanPayImperialOrderCost()) {
    ApplyImperialOrderLpCost();
    return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(9);
  ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = IMPERIAL_ORDER;
    ActivateCardEffectText();
  }
}