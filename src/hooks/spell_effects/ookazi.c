#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

LYN_REPLACE_CHECK(EffectOokazi);
APPEND_TEXT void EffectOokazi__Replacement(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText)
  {
    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(800);
    else
      SetPlayerLifePointsToSubtract(800);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    if (!gHideEffectText)
    {
      gCardEffectTextData.cardId = OOKAZI;
      ActivateCardEffectText();
    }
  }
  else
    ActivateTrapEffect(800);

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
