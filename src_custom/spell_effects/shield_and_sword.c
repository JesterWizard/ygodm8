#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

#define gShieldAndSwordActive (*(u8 *)0x02022EBC)

APPEND_TEXT void EffectShieldAndSword(void)
{
  gShieldAndSwordActive = TRUE;

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = SHIELD_AND_SWORD;
    ActivateCardEffectText();
  }
}
