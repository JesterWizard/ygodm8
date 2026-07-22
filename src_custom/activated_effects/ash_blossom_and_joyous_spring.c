#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateASH_BLOSSOM_AND_JOYOUS_SPRING(void)
{
  if (gMonEffect.id != ASH_BLOSSOM_AND_JOYOUS_SPRING)
    return FALSE;

  /* Printed quick discard negate uses FromHand path. */
  return FALSE;
}

void ActivateASH_BLOSSOM_AND_JOYOUS_SPRINGEffect(void)
{
  Duel_ShowEffectTextTyped(ASH_BLOSSOM_AND_JOYOUS_SPRING, 2);
}

u8 CanActivateAshBlossomFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == ASH_BLOSSOM_AND_JOYOUS_SPRING;
}

u8 TryActivateAshBlossomFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateAshBlossomFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ASH_BLOSSOM_AND_JOYOUS_SPRING, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  /* Ceiling: chain negate for add/SS/mill from Deck not wired; upgrade: chain
   * interrupt hook when one exists. */
  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateAshBlossomFromHand(u8 handZone);
u8 TryActivateAshBlossomFromHand(u8 handZone);
#endif
