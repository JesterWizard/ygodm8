#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 HandHasOtherAmazoness(u8 spyHandZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId;

    if (col == spyHandZone)
      continue;

    cardId = gTurnHands[ACTIVE_DUELIST][col]->id;
    if (cardId != CARD_NONE && Duel_IsAmazonessCard(cardId) && cardId != AMAZONESS_SPY)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateAMAZONESS_SPY(void)
{
  if (gMonEffect.id != AMAZONESS_SPY)
    return FALSE;

  /* ponytail: battle destroy → return Amazoness from GY needs battle hook.
   * Ceiling: SS from hand only; upgrade: reveal + battle recycle. */
  return FALSE;
}

void ActivateAMAZONESS_SPYEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_SPY, 2);
}

u8 CanSpecialSummonAmazonessSpyFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_SPY)
    return FALSE;

  if (!HandHasOtherAmazoness(handZone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessSpyFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAmazonessSpyFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_SPY, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAmazonessSpyFromHand(u8 handZone);
u8 TrySpecialSummonAmazonessSpyFromHand(u8 handZone);
#endif
