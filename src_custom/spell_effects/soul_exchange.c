#include "global.h"
#include "common-chax.h"
#include "soul_exchange.h"
#include "spell_effects.h"

void EffectSoulExchange(void)
{
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  if (!CanActivateSoulExchange())
    return;

  ActivateSoulExchangeForTurn();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SOUL_EXCHANGE;
    ActivateCardEffectText();
  }
}
