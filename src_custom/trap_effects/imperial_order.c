#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"

void ActivateTrapEffect(u16 lp);

#define IMPERIAL_ORDER_LP_COST 700

void EffectImperialOrder(void)
{
  struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ActivateContinuousZone(zone);

  Duel_ShowTrapResponseText(IMPERIAL_ORDER, gTrapEffectData.originCardId);
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

u8 IsImperialOrderActiveOnField(void)
{
  return Duel_IsBackrowCardOnField(IMPERIAL_ORDER, TRUE);
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
    Duel_ChangeLp(ACTIVE_DUELIST, -IMPERIAL_ORDER_LP_COST, TRUE);
    return;
  }

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(IMPERIAL_ORDER, 9);
}
