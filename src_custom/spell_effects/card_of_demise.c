#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "delayed_effects.h"
#include "duel_helpers.h"
#include "spell_effects.h"

APPEND_TEXT void EffectCardOfDemise(void)
{
  u8 turn = WhoseTurn();

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  while (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 5) {
    if (Duel_DrawCards(ACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
      break;
  }

  QueueDelayedDuelEffect(turn, DELAYED_DUEL_EFFECT_CARD_OF_DEMISE);
  Duel_ShowEffectText(CARD_OF_DEMISE);
}
