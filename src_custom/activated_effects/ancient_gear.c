#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 ControlsAncientGearMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsAncientGearMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateANCIENT_GEAR(void)
{
  if (gMonEffect.id != ANCIENT_GEAR)
    return FALSE;

  /* Printed SS is from hand — use FromHand path. */
  return FALSE;
}

void ActivateANCIENT_GEAREffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR, 2);
}

u8 CanSpecialSummonAncientGearFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ANCIENT_GEAR)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return ControlsAncientGearMonster();
}

u8 TrySpecialSummonAncientGearFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAncientGearFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
