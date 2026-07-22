#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateEVIL_HERO_TOXIC_BUBBLE(void)
{
  if (gMonEffect.id != EVIL_HERO_TOXIC_BUBBLE)
    return FALSE;

  /* Ceiling: on-SS draw when Dark Fusion Fusion up needs summon hook. Not
   * field-ignition activatable; SS-from-hand uses FromHand path. */
  return FALSE;
}

void ActivateEVIL_HERO_TOXIC_BUBBLEEffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_TOXIC_BUBBLE, 2);
}

u8 CanSpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != EVIL_HERO_TOXIC_BUBBLE)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Ceiling: HERO-only SS lock + once-per-turn not tracked without turn hook. */
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonEvilHeroToxicBubbleFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(EVIL_HERO_TOXIC_BUBBLE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone);
u8 TrySpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone);
#endif
