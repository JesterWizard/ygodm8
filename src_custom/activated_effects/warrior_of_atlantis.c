#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

unsigned char CanActivateWARRIOR_OF_ATLANTIS(void)
{
  if (gMonEffect.id != WARRIOR_OF_ATLANTIS)
    return FALSE;

  /* Printed effect is hand discard — use FromHand path. */
  return FALSE;
}

void ActivateWARRIOR_OF_ATLANTISEffect(void)
{
  Duel_ShowEffectTextTyped(WARRIOR_OF_ATLANTIS, 2);
}

u8 CanActivateWARRIOR_OF_ATLANTISFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != WARRIOR_OF_ATLANTIS)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, A_LEGENDARY_OCEAN) >= 0;
}

u8 TryActivateWARRIOR_OF_ATLANTISFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateWARRIOR_OF_ATLANTISFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(WARRIOR_OF_ATLANTIS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, A_LEGENDARY_OCEAN, TRUE);
  return TRUE;
}
