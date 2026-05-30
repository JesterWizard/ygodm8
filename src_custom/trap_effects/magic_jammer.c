#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

APPEND_TEXT void EffectMagicJammer(void)
{
  ClearZoneAndSendMonToGraveyard(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST);
  ClearZoneAndSendMonToGraveyard(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol],
                                 ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MAGIC_JAMMER;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}
