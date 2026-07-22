#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateGRAVEKEEPERS_WATCHER(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_WATCHER)
    return FALSE;

  /* Either-turn chain negate when opp discards needs chain/negation hooks
   * outside this file. Not field-ignition; discard-from-hand path below. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_WATCHEREffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_WATCHER, 2);
}

u8 CanActivateGravekeepersWatcherFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == GRAVEKEEPERS_WATCHER;
}

u8 TryActivateGravekeepersWatcherFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateGravekeepersWatcherFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_WATCHER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* negate activation + destroy activated card not wired. */
  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
