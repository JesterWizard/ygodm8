#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

APPEND_TEXT void EffectCardDestruction(void)
{
  u8 activeCount = Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);
  u8 inactiveCount = Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(INACTIVE_DUELIST, FALSE);

  if (Duel_DrawCards(ACTIVE_DUELIST, activeCount, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DrawCards(INACTIVE_DUELIST, inactiveCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(CARD_DESTRUCTION);
}
