#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define gShieldAndSwordActive (*(u8 *)0x02022EBC)

APPEND_TEXT void EffectShieldAndSword(void)
{
  gShieldAndSwordActive = TRUE;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(SHIELD_AND_SWORD);
}
