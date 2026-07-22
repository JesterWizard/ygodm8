#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

unsigned char CanActivateHARPIE_QUEEN(void)
{
  if (gMonEffect.id != HARPIE_QUEEN)
    return FALSE;

  /* Printed discard is hand — use FromHand path; name=Harpie Lady via
   * HarpiePerfumer_TreatsNameAsHarpieLady + Duel_ZoneEffectCardId. */
  return FALSE;
}

void ActivateHARPIE_QUEENEffect(void)
{
  Duel_ShowEffectTextTyped(HARPIE_QUEEN, 2);
}

u8 CanActivateHARPIE_QUEENFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HARPIE_QUEEN)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, HARPIES_HUNTING_GROUND) >= 0;
}

u8 TryActivateHARPIE_QUEENFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateHARPIE_QUEENFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HARPIE_QUEEN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, HARPIES_HUNTING_GROUND, TRUE);
  return TRUE;
}
