#include "global.h"
#include "common-chax.h"

unsigned char CanActivateSkullMarkLadyBug(void) {
  return gMonEffect.id == SKULL_MARK_LADY_BUG;
}

void ActivateSkullMarkLadyBugEffect(void) {
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 controller = gMonEffect.row == 1 ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  ClearZoneAndSendMonToGraveyard(zone, controller);

  if (controller == ACTIVE_DUELIST)
    SetPlayerLifePointsToAdd(3000);
  else
    SetOpponentLifePointsToAdd(3000);

  HandleAtkAndLifePointsAction();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SKULL_MARK_LADY_BUG;
    ActivateCardEffectText();
  }
}
