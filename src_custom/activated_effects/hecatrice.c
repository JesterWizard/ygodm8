#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

u8 CanActivateHecatriceFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HECATRICE)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, VALHALLA_HALL_OF_THE_FALLEN) >= 0;
}

u8 TryActivateHecatriceFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateHecatriceFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HECATRICE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, VALHALLA_HALL_OF_THE_FALLEN, TRUE);
  return TRUE;
}
