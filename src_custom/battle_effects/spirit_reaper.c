#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spirit_reaper.h"

struct SpiritReaperActionData {
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

extern struct SpiritReaperActionData sActionData;

void ClearSpiritReaperDiscardPending(void) {
  gPendingSpiritReaperDiscardDuelist = SPIRIT_REAPER_DISCARD_PENDING_NONE;
}

static u8 FixedToTurnDuelist(u8 fixedDuelist) {
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsSpiritReaperAttacking(u8 duelist) {
  if (duelist == DUEL_PLAYER)
    return sActionData.playerCardId == SPIRIT_REAPER
        && (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4);
  return sActionData.opponentCardId == SPIRIT_REAPER
      && (sActionData.id == 5 || sActionData.id == 6);
}

static u8 DidSpiritReaperDealBattleDamage(u8 attackerDuelist) {
  u16 damage;

  if (!IsSpiritReaperAttacking(attackerDuelist))
    return FALSE;

  if (attackerDuelist == DUEL_PLAYER)
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  else
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];

  return damage > 0;
}

void ApplySpiritReaperDiscardBattleEffect(void) {
  u8 damagedDuelist;

  if (gHideEffectText)
    return;

  if (DidSpiritReaperDealBattleDamage(DUEL_PLAYER))
    damagedDuelist = DUEL_OPPONENT;
  else if (DidSpiritReaperDealBattleDamage(DUEL_OPPONENT))
    damagedDuelist = DUEL_PLAYER;
  else
    return;

  if (Duel_CountCardsInHand(gTurnHands[FixedToTurnDuelist(damagedDuelist)]) == 0)
    return;

  gPendingSpiritReaperDiscardDuelist = damagedDuelist;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveSpiritReaperDiscardBattleEffect();
}

void ResolveSpiritReaperDiscardBattleEffect(void) {
  u8 damagedDuelist;
  u8 turnDuelist;

  damagedDuelist = gPendingSpiritReaperDiscardDuelist;
  if (damagedDuelist == SPIRIT_REAPER_DISCARD_PENDING_NONE)
    return;

  gPendingSpiritReaperDiscardDuelist = SPIRIT_REAPER_DISCARD_PENDING_NONE;
  turnDuelist = FixedToTurnDuelist(damagedDuelist);

  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) == 0)
    return;

  Duel_ShowEffectTextTyped(SPIRIT_REAPER, 3);
  Duel_DiscardRandomFromHand(turnDuelist, 1, FALSE);
}
