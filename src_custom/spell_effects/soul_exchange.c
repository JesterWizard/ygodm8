#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "soul_exchange.h"
#include "spell_effects.h"

void EffectSoulExchange(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (!CanActivateSoulExchange())
    return;

  ActivateSoulExchangeForTurn();
  Duel_ShowEffectText(SOUL_EXCHANGE);
}
