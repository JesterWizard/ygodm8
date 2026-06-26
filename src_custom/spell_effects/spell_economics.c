#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_economics.h"
#include "duel_helpers.h"
#include "imperial_order.h"

static u8 CountFaceUpSpellEconomicsForDuelist(u8 duelist)
{
  u8 row;
  u8 i;
  u8 count = 0;
  u8 backrow;

  if (IsImperialOrderNegatingSpell(SPELL_ECONOMICS))
    return 0;

  if (duelist == DUEL_PLAYER)
    backrow = PLAYER_BACKROW;
  else
    backrow = OPPONENT_BACKROW;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[backrow][i];
    if (zone != NULL && zone->id == SPELL_ECONOMICS && zone->isFaceUp == TRUE)
      count++;
  }

  return count;
}

u8 IsSpellEconomicsActiveForActiveDuelist(void)
{
  u8 duelist;

  if (WhoseTurn() == DUEL_PLAYER)
    duelist = DUEL_PLAYER;
  else
    duelist = DUEL_OPPONENT;

  return CountFaceUpSpellEconomicsForDuelist(duelist) > 0;
}

APPEND_TEXT void EffectSpellEconomics(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SPELL_ECONOMICS;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }
}
