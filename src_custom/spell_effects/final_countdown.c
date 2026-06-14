#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "final_countdown.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define FINAL_COUNTDOWN_LP_COST 2000
#define FINAL_COUNTDOWN_WIN_TURNS 20

extern void DeclareLoser(unsigned char);

u8 CanActivateFinalCountdown(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= FINAL_COUNTDOWN_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= FINAL_COUNTDOWN_LP_COST;
}

u8 IsActivatedFinalCountdownZone(const struct DuelCard *zone)
{
  return zone != NULL
      && zone->id == FINAL_COUNTDOWN
      && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE;
}

static void PayLpCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(FINAL_COUNTDOWN_LP_COST);
  else
    SetOpponentLifePointsToSubtract(FINAL_COUNTDOWN_LP_COST);
}

static u8 BackrowOwner(u8 fixedRow)
{
  return (fixedRow == PLAYER_BACKROW) ? DUEL_PLAYER : DUEL_OPPONENT;
}

static void TryWinFromFinalCountdown(u8 fixedRow, const struct DuelCard *zone)
{
  if (zone->permStage < FINAL_COUNTDOWN_WIN_TURNS)
    return;

  if (IsImperialOrderNegatingSpell(FINAL_COUNTDOWN))
    return;

  if (BackrowOwner(fixedRow) == DUEL_PLAYER)
    DeclareLoser(DUEL_OPPONENT);
  else
    DeclareLoser(DUEL_PLAYER);
}

static void AgeFinalCountdownOnBackrow(u8 fixedRow)
{
  u8 i;
  struct DuelCard *zone;

  if (IsImperialOrderNegatingSpell(FINAL_COUNTDOWN))
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[fixedRow][i];
    if (!IsActivatedFinalCountdownZone(zone))
      continue;

    IncrementPermStage(zone);
    TryWinFromFinalCountdown(fixedRow, zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

void AgeFinalCountdownTurns(void)
{
  AgeFinalCountdownOnBackrow(PLAYER_BACKROW);
  if (IsDuelOver() == TRUE)
    return;

  AgeFinalCountdownOnBackrow(OPPONENT_BACKROW);
}

APPEND_TEXT void EffectFinalCountdown(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateFinalCountdown())
    return;

  PayLpCost();
  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (IsDuelOver() == TRUE)
    return;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ResetPermStage(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = FINAL_COUNTDOWN;
    ActivateCardEffectText();
  }
}

#if !defined(__GNUC__)
void EffectFinalCountdown(void);
#endif
