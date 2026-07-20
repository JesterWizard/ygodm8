#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

unsigned char CanActivateCHARM_OF_SHABTI(void)
{
  if (gMonEffect.id != CHARM_OF_SHABTI)
    return FALSE;

  /* Printed effect is hand discard — use FromHand path. */
  return FALSE;
}

void ActivateCHARM_OF_SHABTIEffect(void)
{
  Duel_ShowEffectTextTyped(CHARM_OF_SHABTI, 2);
}

u8 CanActivateCHARM_OF_SHABTIFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == CHARM_OF_SHABTI;
}

u8 TryActivateCHARM_OF_SHABTIFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateCHARM_OF_SHABTIFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(CHARM_OF_SHABTI, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* ponytail: battle protection for Gravekeeper's monsters not applied.
   * Ceiling: discard only; upgrade: battle-destroy immunity gate until EP. */
  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  return TRUE;
}
