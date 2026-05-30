#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

void EnableDoubleSummonForTurn(void);

APPEND_TEXT void EffectDoubleSummon(void)
{
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  EnableDoubleSummonForTurn();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = DOUBLE_SUMMON;
    ActivateCardEffectText();
  }
}
