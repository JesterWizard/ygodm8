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

  Duel_DrawCardsUntilHandSize(ACTIVE_DUELIST, 5, FALSE);

  QueueDelayedDuelEffect(turn, DELAYED_DUEL_EFFECT_CARD_OF_DEMISE);
  Duel_ShowEffectText(CARD_OF_DEMISE);
}
