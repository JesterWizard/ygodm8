#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mefist_the_infernal_general.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct MefistTheInfernalGeneralActionData {
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

extern struct MefistTheInfernalGeneralActionData sActionData;

void ClearMefistDiscardPending(void) {
  gPendingMefistDiscardDuelist = MEFIST_DISCARD_PENDING_NONE;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 IsMefistAttacking(u8 duelist) {
  if (duelist == DUEL_PLAYER)
    return sActionData.playerCardId == MEFIST_THE_INFERNAL_GENERAL
        && (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4);
  return sActionData.opponentCardId == MEFIST_THE_INFERNAL_GENERAL
      && (sActionData.id == 1 || sActionData.id == 5 || sActionData.id == 6);
}

static void ApplyPiercingDamageToOpponent(u16 damage) {
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }

  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyPiercingDamageToPlayer(u16 damage) {
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }

  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

static void ApplyMefistPiercingDamage(void) {
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2 && sActionData.playerCardId == MEFIST_THE_INFERNAL_GENERAL) {
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    if (attackerAtk <= defenderDef)
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
      return;

    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToOpponent(damage);
    return;
  }

  if (sActionData.id == 5 && sActionData.opponentCardId == MEFIST_THE_INFERNAL_GENERAL) {
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    if (attackerAtk <= defenderDef)
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_PLAYER))
      return;

    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToPlayer(damage);
  }
}

static u8 CountCardsInDuelistHand(u8 duelist) {
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gDuel.hands[duelist][i].id != CARD_NONE)
      count++;

  return count;
}

static u8 PickRandomHandZone(u8 duelist) {
  u8 i;
  u8 occupied = CountCardsInDuelistHand(duelist);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[duelist][i].id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void DiscardRandomHandCard(u8 duelist) {
  u8 zone = PickRandomHandZone(duelist);

  if (zone == 0xFF)
    return;

  ClearZoneAndSendMonToGraveyard(&gDuel.hands[duelist][zone], duelist);
}

static u8 DidMefistDealBattleDamage(u8 attackerDuelist) {
  u16 damage;

  if (!IsMefistAttacking(attackerDuelist))
    return FALSE;

  if (attackerDuelist == DUEL_PLAYER)
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  else
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];

  return damage > 0;
}

void ApplyMefistTheInfernalGeneralPiercingBattleEffect(void) {
  if (sActionData.playerCardId != MEFIST_THE_INFERNAL_GENERAL
      && sActionData.opponentCardId != MEFIST_THE_INFERNAL_GENERAL)
    return;
  if (!IsMonsterBattleAction(sActionData.id))
    return;

  ApplyMefistPiercingDamage();
}

void ApplyMefistTheInfernalGeneralDiscardBattleEffect(void) {
  u8 damagedDuelist;

  if (gHideEffectText)
    return;

  if (DidMefistDealBattleDamage(DUEL_PLAYER))
    damagedDuelist = DUEL_OPPONENT;
  else if (DidMefistDealBattleDamage(DUEL_OPPONENT))
    damagedDuelist = DUEL_PLAYER;
  else
    return;

  if (CountCardsInDuelistHand(damagedDuelist) == 0)
    return;

  gPendingMefistDiscardDuelist = damagedDuelist;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveMefistTheInfernalGeneralDiscardBattleEffect();
}

void ResolveMefistTheInfernalGeneralDiscardBattleEffect(void) {
  u8 damagedDuelist;

  damagedDuelist = gPendingMefistDiscardDuelist;
  if (damagedDuelist == MEFIST_DISCARD_PENDING_NONE)
    return;

  gPendingMefistDiscardDuelist = MEFIST_DISCARD_PENDING_NONE;

  if (CountCardsInDuelistHand(damagedDuelist) == 0)
    return;

  Duel_ShowEffectTextTyped(MEFIST_THE_INFERNAL_GENERAL, 3);
  DiscardRandomHandCard(damagedDuelist);
}
