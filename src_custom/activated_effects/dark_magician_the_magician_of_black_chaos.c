#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 FieldHasShiningSarcophagus(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == SHINING_SARCOPHAGUS)
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS(void)
{
  if (gMonEffect.id != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS)
    return FALSE;

  /* ponytail: name=DM + destroy-revive/Set need name/destroy hooks.
   * Ceiling: not field-ignition; FromHand if Shining Sarcophagus. */
  return FALSE;
}

void ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOSEffect(void)
{
  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS, 2);
}

u8 CanSpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id
      != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS)
    return FALSE;

  if (!FieldHasShiningSarcophagus())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(u8 handZone);
u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(u8 handZone);
#endif
