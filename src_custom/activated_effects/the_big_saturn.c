#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "the_big_saturn.h"

static u8 HasEnoughLifePoints(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= THE_BIG_SATURN_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= THE_BIG_SATURN_LP_COST;
}

unsigned char CanActivateTheBigSaturn(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_BIG_SATURN)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return HasEnoughLifePoints();
}

void ActivateTheBigSaturnEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(THE_BIG_SATURN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(WhoseTurn(), -THE_BIG_SATURN_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  IncrementPermStage(zone);
  IncrementPermStage(zone);
  zone->unkThree = TRUE;
}

void ClearTheBigSaturnAtkBoostAtEndOfTurn(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone->id != THE_BIG_SATURN || !zone->unkThree)
        continue;

      DecrementPermStage(zone);
      DecrementPermStage(zone);
      zone->unkThree = FALSE;
    }
  }
}
