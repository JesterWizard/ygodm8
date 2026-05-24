#include "global.h"
#include "common-chax.h"

unsigned char CanActivateKarateMan(void) {
  return gMonEffect.id == KARATE_MAN;
}

void ActivateKarateManEffect(void) {
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  IncrementPermStage(zone);
  IncrementPermStage(zone);
  zone->unkThree = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = KARATE_MAN;
    ActivateCardEffectText();
  }
}

void DestroyKarateManAtEndOfTurn(void) {
  u8 row;

  for (row = 1; row <= 2; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone->id == KARATE_MAN && zone->unkThree == TRUE) {
        ClearZoneAndSendMonToGraveyard(zone, row == 2 ? ACTIVE_DUELIST : INACTIVE_DUELIST);
      }
    }
  }
}
