#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "don_zaloog.h"

struct DonZaloogActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct DonZaloogActionData sActionData;

void ClearDonZaloogPending(void)
{
  gPendingDonZaloogTargetDuelist = DON_ZALOOG_PENDING_NONE;
}

static u8 FixedToTurnDuelist(u8 fixedDuelist)
{
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsDonZaloogAttacking(u8 duelist)
{
  if (duelist == DUEL_PLAYER)
    return sActionData.playerCardId == DON_ZALOOG
        && (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4);
  return sActionData.opponentCardId == DON_ZALOOG
      && (sActionData.id == 5 || sActionData.id == 6);
}

static u8 DidDonZaloogDealBattleDamage(u8 attackerDuelist)
{
  u16 damage;

  if (!IsDonZaloogAttacking(attackerDuelist))
    return FALSE;

  if (attackerDuelist == DUEL_PLAYER)
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  else
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];

  return damage > 0;
}

void ApplyDonZaloogBattleEffect(void)
{
  u8 damagedDuelist;

  if (gHideEffectText)
    return;

  if (DidDonZaloogDealBattleDamage(DUEL_PLAYER))
    damagedDuelist = DUEL_OPPONENT;
  else if (DidDonZaloogDealBattleDamage(DUEL_OPPONENT))
    damagedDuelist = DUEL_PLAYER;
  else
    return;

  gPendingDonZaloogTargetDuelist = damagedDuelist;

  if (gUnk2023EA0.unk18 == 0)
    ResolveDonZaloogBattleEffect();
}

void ResolveDonZaloogBattleEffect(void)
{
  u8 damagedDuelist;
  u8 turnDuelist;

  damagedDuelist = gPendingDonZaloogTargetDuelist;
  if (damagedDuelist == DON_ZALOOG_PENDING_NONE)
    return;

  gPendingDonZaloogTargetDuelist = DON_ZALOOG_PENDING_NONE;
  turnDuelist = FixedToTurnDuelist(damagedDuelist);

  Duel_ShowEffectTextTyped(DON_ZALOOG, 3);

  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) > 0) {
    Duel_DiscardRandomFromHand(turnDuelist, 1, FALSE);
    return;
  }

  Duel_MillTopDeckCards(turnDuelist, 2, FALSE);
}
