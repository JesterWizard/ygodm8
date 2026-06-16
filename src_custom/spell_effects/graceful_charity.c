#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define GRACEFUL_CHARITY_DRAW_COUNT 3
#define GRACEFUL_CHARITY_DISCARD_COUNT 2

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

APPEND_TEXT void EffectGracefulCharity(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(GRACEFUL_CHARITY);

  if (IsDuelOver() != TRUE) {
    if (Duel_DrawCards(ACTIVE_DUELIST, GRACEFUL_CHARITY_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    if (IsDuelOver() != TRUE)
      Duel_DiscardFromHand(ACTIVE_DUELIST, GRACEFUL_CHARITY_DISCARD_COUNT, AnyHandCard, TRUE);
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}
