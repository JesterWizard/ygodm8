#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

APPEND_TEXT void EffectJamBreedingMachine(void)
{
  if (NumEmptyZonesInRow(gTurnZones[2]) > 0) {
    u8 zone = FirstEmptyZoneInRow(gTurnZones[2]);

    gTurnZones[2][zone]->id = CHANGE_SLIME;
    gTurnZones[2][zone]->isDefending = FALSE;
    FlipCardFaceUp(gTurnZones[2][zone]);
  }

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  UnblockSummoning(ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = JAM_BREEDING_MACHINE;
    ActivateCardEffectText();
  }
}
