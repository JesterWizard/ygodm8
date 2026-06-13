#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "coffin_seller.h"
#include "dynamic_equip.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "skull_invitation.h"

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

static u8 MonsterSlotBit(const struct DuelCard *zone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone)
        return (row - OPPONENT_MONSTER_ROW) * MAX_ZONES_IN_ROW + col;
    }
  }

  return 0xFF;
}

static u8 LeaveAlreadyTriggered(const struct DuelCard *zone)
{
  u8 bit = MonsterSlotBit(zone);

  if (bit >= COFFIN_SELLER_MONSTER_SLOTS)
    return FALSE;

  return (sTriggeredLeaveMask & (1 << bit)) != 0;
}

static void MarkLeaveTriggered(const struct DuelCard *zone)
{
  u8 bit = MonsterSlotBit(zone);

  if (bit < COFFIN_SELLER_MONSTER_SLOTS)
    sTriggeredLeaveMask |= (1 << bit);
}

static struct DuelCard *FindCoffinSellerZone(u8 duelist)
{
  u8 backrow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[backrow][i]->id == COFFIN_SELLER)
      return gFixedZones[backrow][i];
  }

  return NULL;
}

static void FlipCoffinSellerFaceUp(struct DuelCard *zone)
{
  if (zone->isFaceUp == FALSE) {
    FlipCardFaceUp(zone);
    zone->isLocked = TRUE;
  }
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
  u8 hideEffectText = gHideEffectText;

  if (targetDuelist == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(COFFIN_SELLER_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(COFFIN_SELLER_DAMAGE);

  if (!hideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = COFFIN_SELLER;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }

  gHideEffectText = TRUE;
  HandleAtkAndLifePointsAction();
  gHideEffectText = hideEffectText;
  CheckLoserFlags();
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

  if (LeaveAlreadyTriggered(zone))
    return;

  owner = GetDuelistForZone(zone);
  if (owner == DUEL_OPPONENT) {
    sellerZone = FindCoffinSellerZone(DUEL_PLAYER);
    if (sellerZone == NULL)
      return;

    MarkLeaveTriggered(zone);
    FlipCoffinSellerFaceUp(sellerZone);
    QueueCoffinSellerDamage(DUEL_OPPONENT);
  } else if (owner == DUEL_PLAYER) {
    sellerZone = FindCoffinSellerZone(DUEL_OPPONENT);
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
