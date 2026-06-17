#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "coffin_seller.h"
#include "dynamic_equip.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "skull_invitation.h"
#include "imperial_order.h"

#define COFFIN_SELLER_DAMAGE 300
#define COFFIN_SELLER_MONSTER_SLOTS (MAX_ZONES_IN_ROW * 2)

extern u8 gSuppressSkullInvitationDamage;

static u16 sTriggeredLeaveMask APPEND_DATA = 0;

static u8 ZoneWasMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
      || EmbodimentOfApophisZoneIsMonsterForm(zone)
      || OjamaTrioZoneIsMonsterForm(zone);
}

static u8 LeaveAlreadyTriggered(const struct DuelCard *zone)
{
  u8 bit = Duel_FixedMonsterSlotBit(zone);

  if (bit >= COFFIN_SELLER_MONSTER_SLOTS)
    return FALSE;

  return (sTriggeredLeaveMask & (1 << bit)) != 0;
}

static void MarkLeaveTriggered(const struct DuelCard *zone)
{
  u8 bit = Duel_FixedMonsterSlotBit(zone);

  if (bit < COFFIN_SELLER_MONSTER_SLOTS)
    sTriggeredLeaveMask |= (1 << bit);
}

static void FlipCoffinSellerFaceUp(struct DuelCard *zone)
{
  if (zone->isFaceUp == FALSE)
    Duel_ActivateContinuousZone(zone);
}

u8 IsNonSelectableCoffinSellerZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == COFFIN_SELLER;
}

void ClearCoffinSellerPending(void)
{
  gPendingCoffinSellerDamageToPlayer = 0;
  gPendingCoffinSellerDamageToOpponent = 0;
  sTriggeredLeaveMask = 0;
}

static void ApplyCoffinSellerDamage(u8 targetDuelist)
{
  Duel_ChangeLpWithPrefaceText(Duel_TurnDuelistMatchingWhoseTurn(targetDuelist),
                               -COFFIN_SELLER_DAMAGE, COFFIN_SELLER, 3, FALSE);
}

static void QueueCoffinSellerDamage(u8 targetDuelist)
{
  if (targetDuelist == DUEL_PLAYER) {
    if (gPendingCoffinSellerDamageToPlayer < 255)
      gPendingCoffinSellerDamageToPlayer++;
  } else if (gPendingCoffinSellerDamageToOpponent < 255) {
    gPendingCoffinSellerDamageToOpponent++;
  }
}

void ResolveCoffinSellerBattleEffect(void)
{
  u8 i;
  u8 oppPending;
  u8 playerPending;

  if (gHideEffectText)
    return;

  oppPending = gPendingCoffinSellerDamageToOpponent;
  playerPending = gPendingCoffinSellerDamageToPlayer;

  if (oppPending == 0 && playerPending == 0)
    return;

  gPendingCoffinSellerDamageToOpponent = 0;
  gPendingCoffinSellerDamageToPlayer = 0;
  sTriggeredLeaveMask = 0;

  for (i = 0; i < oppPending; i++) {
    ApplyCoffinSellerDamage(DUEL_OPPONENT);
    if (IsDuelOver() == TRUE)
      break;
  }

  for (i = 0; i < playerPending; i++) {
    ApplyCoffinSellerDamage(DUEL_PLAYER);
    if (IsDuelOver() == TRUE)
      break;
  }
}

void TryApplyCoffinSellerOnFieldLeave(struct DuelCard *zone)
{
  u8 suppress = gSuppressSkullInvitationDamage;
  u8 owner;
  struct DuelCard *sellerZone;

  gSuppressSkullInvitationDamage = FALSE;

  if (suppress || gHideEffectText)
    return;

  if (!ZoneWasMonster(zone))
    return;

  if (IsImperialOrderNegatingSpell(COFFIN_SELLER))
    return;

  if (LeaveAlreadyTriggered(zone))
    return;

  owner = GetDuelistForZone(zone);
  if (owner == DUEL_OPPONENT) {
    sellerZone = Duel_FindBackrowCard(DUEL_PLAYER, COFFIN_SELLER, FALSE);
    if (sellerZone == NULL)
      return;

    MarkLeaveTriggered(zone);
    FlipCoffinSellerFaceUp(sellerZone);
    QueueCoffinSellerDamage(DUEL_OPPONENT);
  } else if (owner == DUEL_PLAYER) {
    sellerZone = Duel_FindBackrowCard(DUEL_OPPONENT, COFFIN_SELLER, FALSE);
    if (sellerZone == NULL)
      return;

    MarkLeaveTriggered(zone);
    FlipCoffinSellerFaceUp(sellerZone);
    QueueCoffinSellerDamage(DUEL_PLAYER);
  }
}

APPEND_TEXT void EffectCoffinSeller(void)
{
}
