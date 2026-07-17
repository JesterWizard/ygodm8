#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "guardian_treasure.h"
#include "drop_off.h"
#include "imperial_order.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define GUARDIAN_TREASURE_DISCARD_COST 4
#define GUARDIAN_TREASURE_DRAW_COUNT 2

static void DiscardFirstCardsInHand(struct DuelCard **hand, u8 count)
{
  u8 i;
  u8 discarded = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (hand[i]->id != CARD_NONE) {
      GraveyardExpand_PushTurn(ACTIVE_DUELIST, hand[i]->id);
      hand[i]->id = CARD_NONE;
      discarded++;

      if (discarded >= count)
        break;
    }
  }
}

static u8 HandHasDrawRoom(u8 turn)
{
  return SixCardHand_HasDrawRoom(turn);
}

static void DrawCardsForTurn(u8 turn, u8 count)
{
  while (count > 0) {
    if (!HandHasDrawRoom(turn))
      return;

    TryDrawingCard(turn);
    if (IsDuelOver() == TRUE)
      return;

    count--;
  }
}

u8 IsGuardianTreasureActiveOnField(void)
{
  u8 i;

  if (IsImperialOrderNegatingSpell(GUARDIAN_TREASURE))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id == GUARDIAN_TREASURE
        && gTurnZones[ACTIVE_DUELIST_BACKROW][i]->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateGuardianTreasure(void)
{
  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) >= GUARDIAN_TREASURE_DISCARD_COST;
}

void PerformGuardianTreasureDrawPhaseDraws(u8 turn)
{
  u8 drawCount = IsGuardianTreasureActiveOnField()
      ? GUARDIAN_TREASURE_DRAW_COUNT
      : 1;

  BeginDrawPhaseNormalDraws();
  DrawCardsForTurn(turn, drawCount);
  EndDrawPhaseNormalDraws();
}

APPEND_TEXT void EffectGuardianTreasure(void)
{
  u8 turn = WhoseTurn();
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateGuardianTreasure())
    return;

  DiscardFirstCardsInHand(gTurnHands[ACTIVE_DUELIST], GUARDIAN_TREASURE_DISCARD_COST);

  Duel_ActivateContinuousZone(zone);

  DrawCardsForTurn(turn, GUARDIAN_TREASURE_DRAW_COUNT);
  Duel_ShowEffectText(GUARDIAN_TREASURE);
}
