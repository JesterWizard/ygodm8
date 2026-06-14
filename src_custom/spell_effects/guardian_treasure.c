#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "guardian_treasure.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define GUARDIAN_TREASURE_DISCARD_COST 4
#define GUARDIAN_TREASURE_DRAW_COUNT 2

static u8 CountCardsInHand(struct DuelCard **hand)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (hand[i]->id != CARD_NONE)
      count++;

  return count;
}

static void DiscardFirstCardsInHand(struct DuelCard **hand, u8 count)
{
  u8 i;
  u8 discarded = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (hand[i]->id != CARD_NONE)
    {
      gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = hand[i]->id;
      hand[i]->id = CARD_NONE;
      discarded++;

      if (discarded >= count)
        break;
    }
  }
}

static void DrawCardsForTurn(u8 turn, u8 count)
{
  u8 i;

  while (count > 0)
  {
    u8 drew = FALSE;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    {
      if (gDuel.hands[turn][i].id != CARD_NONE)
        continue;

      TryDrawingCard(turn);
      drew = TRUE;
      break;
    }

    if (!drew || IsDuelOver() == TRUE)
      return;

    count--;
  }
}

u8 IsGuardianTreasureActiveOnField(void)
{
  u8 i;

  if (IsImperialOrderNegatingSpell(GUARDIAN_TREASURE))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id == GUARDIAN_TREASURE
        && gTurnZones[ACTIVE_DUELIST_BACKROW][i]->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateGuardianTreasure(void)
{
  return CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) >= GUARDIAN_TREASURE_DISCARD_COST;
}

void PerformGuardianTreasureDrawPhaseDraws(u8 turn)
{
  u8 drawCount = IsGuardianTreasureActiveOnField()
      ? GUARDIAN_TREASURE_DRAW_COUNT
      : 1;

  DrawCardsForTurn(turn, drawCount);
}

APPEND_TEXT void EffectGuardianTreasure(void)
{
  u8 turn = WhoseTurn();
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateGuardianTreasure())
    return;

  DiscardFirstCardsInHand(gTurnHands[ACTIVE_DUELIST], GUARDIAN_TREASURE_DISCARD_COST);

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  DrawCardsForTurn(turn, GUARDIAN_TREASURE_DRAW_COUNT);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = GUARDIAN_TREASURE;
    ActivateCardEffectText();
  }
}
