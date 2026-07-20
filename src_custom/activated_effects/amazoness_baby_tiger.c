#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateAMAZONESS_BABY_TIGER(void)
{
  if (gMonEffect.id != AMAZONESS_BABY_TIGER)
    return FALSE;

  /* ponytail: Amazoness-Tiger name + GY ATK boost need continuous hooks.
   * Ceiling: SS from hand only; upgrade: on Amazoness summon trigger. */
  return FALSE;
}

void ActivateAMAZONESS_BABY_TIGEREffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_BABY_TIGER, 2);
}

u8 CanSpecialSummonAmazonessBabyTigerFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_BABY_TIGER)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessBabyTigerFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAmazonessBabyTigerFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_BABY_TIGER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAmazonessBabyTigerFromHand(u8 handZone);
u8 TrySpecialSummonAmazonessBabyTigerFromHand(u8 handZone);
#endif
