#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void EffectCardOfSanctity(void);

APPEND_TEXT void EffectCardOfSanctity(void)
{
  u8 i;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(ACTIVE_DUELIST, FALSE);
  Duel_DestroyAllHandCards(INACTIVE_DUELIST, FALSE);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (Duel_DrawCards(ACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
    if (Duel_DrawCards(INACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CARD_OF_SANCTITY;
    gCardEffectTextData.cardId2 = 0;
    ActivateCardEffectText();
  }
}
