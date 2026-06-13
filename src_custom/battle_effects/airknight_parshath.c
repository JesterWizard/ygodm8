#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "airknight_parshath.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct AirknightParshathActionData {
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

extern struct AirknightParshathActionData sActionData;

void ClearAirknightParshathDrawPending(void) {
  gPendingAirknightParshathDrawDuelist = AIRKNIGHT_PARSHATH_DRAW_PENDING_NONE;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 IsAirknightAttacking(u8 duelist) {
  if (duelist == DUEL_PLAYER)
    return sActionData.playerCardId == AIRKNIGHT_PARSHATH
        && (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4);
  return sActionData.opponentCardId == AIRKNIGHT_PARSHATH
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

static void ApplyAirknightPiercingDamage(void) {
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2 && sActionData.playerCardId == AIRKNIGHT_PARSHATH) {
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

  if (sActionData.id == 5 && sActionData.opponentCardId == AIRKNIGHT_PARSHATH) {
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

static u8 HasEmptyHandSlot(u8 duelist) {
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gDuel.hands[duelist][i].id == CARD_NONE)
      return TRUE;

  return FALSE;
}

static u8 DidAirknightDealBattleDamage(u8 attackerDuelist) {
  u16 damage;

  if (!IsAirknightAttacking(attackerDuelist))
    return FALSE;

  if (attackerDuelist == DUEL_PLAYER)
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  else
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];

  return damage > 0;
}

static void ShowAirknightEffectText(void) {
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(3);
  gCardEffectTextData.cardId = AIRKNIGHT_PARSHATH;
  ActivateCardEffectText();
}

void ApplyAirknightParshathPiercingBattleEffect(void) {
  if (sActionData.playerCardId != AIRKNIGHT_PARSHATH
      && sActionData.opponentCardId != AIRKNIGHT_PARSHATH)
    return;
  if (!IsMonsterBattleAction(sActionData.id))
    return;

  ApplyAirknightPiercingDamage();
}

void ApplyAirknightParshathDrawBattleEffect(void) {
  u8 attackerDuelist;

  if (gHideEffectText)
    return;

  if (DidAirknightDealBattleDamage(DUEL_PLAYER))
    attackerDuelist = DUEL_PLAYER;
  else if (DidAirknightDealBattleDamage(DUEL_OPPONENT))
    attackerDuelist = DUEL_OPPONENT;
  else
    return;

  if (!HasEmptyHandSlot(attackerDuelist))
    return;

  gPendingAirknightParshathDrawDuelist = attackerDuelist;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveAirknightParshathDrawBattleEffect();
}

void ResolveAirknightParshathDrawBattleEffect(void) {
  u8 duelist;

  duelist = gPendingAirknightParshathDrawDuelist;
  if (duelist == AIRKNIGHT_PARSHATH_DRAW_PENDING_NONE)
    return;

  gPendingAirknightParshathDrawDuelist = AIRKNIGHT_PARSHATH_DRAW_PENDING_NONE;

  if (!HasEmptyHandSlot(duelist))
    return;

  ShowAirknightEffectText();
  TryDrawingCard(duelist);
}
