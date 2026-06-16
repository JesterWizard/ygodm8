#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

APPEND_TEXT void EffectJamBreedingMachine(void)
{
  if (NumEmptyZonesInRow(gTurnZones[2]) > 0) {
    u8 zone = FirstEmptyZoneInRow(gTurnZones[2]);

    gTurnZones[2][zone]->id = CHANGE_SLIME;
    gTurnZones[2][zone]->isDefending = FALSE;
    FlipCardFaceUp(gTurnZones[2][zone]);
  }

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  UnblockSummoning(ACTIVE_DUELIST);
  Duel_ShowEffectText(JAM_BREEDING_MACHINE);
}
