#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void EnableDoubleSummonForTurn(void);

APPEND_TEXT void EffectDoubleSummon(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);
  EnableDoubleSummonForTurn();
  Duel_ShowEffectText(DOUBLE_SUMMON);
}
