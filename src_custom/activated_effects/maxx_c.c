#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 IsMaxxC(u16 cardId)
{
  return cardId == MAXX_C;
}

unsigned char CanActivateMAXX_C(void)
{
  if (gMonEffect.id != MAXX_C)
    return FALSE;

  /* Printed effect sends from hand during either turn — use FromHand path. */
  return FALSE;
}

void ActivateMAXX_CEffect(void)
{
  Duel_ShowEffectTextTyped(MAXX_C, 2);
}

u8 CanActivateMAXX_CFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == MAXX_C;
}

u8 TryActivateMAXX_CFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateMAXX_CFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MAXX_C, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  /* ponytail: draw-on-opponent-Special-Summon this turn not wired; upgrade: SS
   * hook + simple turn flag when one exists. */
  UpdateDuelGfxExceptField();
  return TRUE;
}
