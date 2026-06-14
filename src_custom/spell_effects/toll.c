#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"
#include "toll.h"
#include "imperial_order.h"

#define TOLL_LP_PER_MONSTER 500

u8 IsActivatedTollZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == TOLL && zone->isFaceUp == TRUE;
}

u8 IsTollActiveOnField(void)
{
  u8 row;
  u8 i;

  if (IsImperialOrderNegatingSpell(TOLL))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gFixedZones[row][i]->id == TOLL)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CountActiveDuelistMonsters(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static u16 GetTollAttackCost(void)
{
  u8 monsterCount = CountActiveDuelistMonsters();

  if (monsterCount == 0)
    return 0;

  return (u16)monsterCount * TOLL_LP_PER_MONSTER;
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

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(cost);
  else
    SetOpponentLifePointsToSubtract(cost);

  gHideEffectText = TRUE;
  HandleAtkAndLifePointsAction();
  gHideEffectText = hideEffectText;
  CheckLoserFlags();
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

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = TOLL;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }
}
