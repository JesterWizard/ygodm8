#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

unsigned char CanActivateGRAVEKEEPERS_COMMANDANT(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_COMMANDANT)
    return FALSE;

  /* Printed effect is hand discard — use FromHand path. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_COMMANDANTEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_COMMANDANT, 2);
}

u8 CanActivateGRAVEKEEPERS_COMMANDANTFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GRAVEKEEPERS_COMMANDANT)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, NECROVALLEY) >= 0;
}

u8 TryActivateGRAVEKEEPERS_COMMANDANTFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateGRAVEKEEPERS_COMMANDANTFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_COMMANDANT, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, NECROVALLEY, TRUE);
  return TRUE;
}
