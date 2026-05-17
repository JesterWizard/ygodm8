#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

void EffectCardOfSanctity(void);

APPEND_TEXT void EffectCardOfSanctity(void)
{
  u8 i;

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    ClearZoneAndSendMonToGraveyard(gTurnHands[ACTIVE_DUELIST][i], ACTIVE_DUELIST);
    ClearZoneAndSendMonToGraveyard(gTurnHands[INACTIVE_DUELIST][i], INACTIVE_DUELIST);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    TryDrawingCard(ACTIVE_DUELIST);
    TryDrawingCard(INACTIVE_DUELIST);
  }

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = CARD_OF_SANCTITY;
    gCardEffectTextData.cardId2 = 0;
    ActivateCardEffectText();
  }
}
