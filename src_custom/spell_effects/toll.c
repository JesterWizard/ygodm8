#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "toll.h"
#include "imperial_order.h"

#define TOLL_LP_COST 500

u8 IsActivatedTollZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == TOLL && zone->isFaceUp == TRUE;
}

static u8 CountFaceUpTollsOnField(void)
{
  u8 row;
  u8 i;
  u8 count = 0;

  if (IsImperialOrderNegatingSpell(TOLL))
    return 0;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsActivatedTollZone(gFixedZones[row][i]))
        count++;
    }
  }

  return count;
}

u8 IsTollActiveOnField(void)
{
  return CountFaceUpTollsOnField() != 0;
}

static u16 GetTollAttackCost(void)
{
  u8 tollCount = CountFaceUpTollsOnField();

  if (tollCount == 0)
    return 0;

  return (u16)tollCount * TOLL_LP_COST;
}

static u8 ActiveDuelistCanPayTollAttackCost(u16 cost)
{
  if (cost == 0)
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= cost;

  return gDuelLifePoints[DUEL_OPPONENT] >= cost;
}

static void ApplyTollAttackLpCost(u16 cost)
{
  u8 hideEffectText = gHideEffectText;

  if (cost == 0)
    return;

  gHideEffectText = TRUE;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)cost, TRUE);
  gHideEffectText = hideEffectText;
}

u8 TryPayTollAttackCost(void)
{
  u16 cost;

  if (!IsTollActiveOnField())
    return TRUE;

  cost = GetTollAttackCost();
  if (!ActiveDuelistCanPayTollAttackCost(cost))
    return FALSE;

  ApplyTollAttackLpCost(cost);

  return IsDuelOver() != TRUE;
}

APPEND_TEXT void EffectToll(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = TOLL;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }
}
