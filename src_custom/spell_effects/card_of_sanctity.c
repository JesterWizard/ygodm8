#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void EffectCardOfSanctity(void);

APPEND_TEXT void EffectCardOfSanctity(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(INACTIVE_DUELIST, FALSE);

  if (Duel_DrawCardsUntilHandSize(ACTIVE_DUELIST, 5, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;
  if (Duel_DrawCardsUntilHandSize(INACTIVE_DUELIST, 5, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CARD_OF_SANCTITY;
    gCardEffectTextData.cardId2 = 0;
    ActivateCardEffectText();
  }
}
