#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateDESTINY_HERO_DYNATAG(void)
{
  if (gMonEffect.id != DESTINY_HERO_DYNATAG)
    return FALSE;

  /* ponytail: Damage Step no-battle-damage + GY banish ATK boost use FromHand
   * path. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateDESTINY_HERO_DYNATAGEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DYNATAG, 2);
}

u8 CanActivateDestinyHeroDynatagFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == DESTINY_HERO_DYNATAG;
}

u8 TryActivateDestinyHeroDynatagFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateDestinyHeroDynatagFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DYNATAG, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* ponytail: no battle damage from that battle not wired; both players 1000. */
  if (Duel_ChangeLp(ACTIVE_DUELIST, -1000, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateDestinyHeroDynatagFromHand(u8 handZone);
u8 TryActivateDestinyHeroDynatagFromHand(u8 handZone);
#endif
