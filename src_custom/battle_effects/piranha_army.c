#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "piranha_army.h"

#define FLAG_LOSER_OPPONENT 16
#define FLAG_LOSER_PLAYER 4

struct PiranhaArmyActionData {
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

extern struct PiranhaArmyActionData sActionData;

static void ApplyDirectDamageToOpponent(u16 damage) {
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

static void ApplyDirectDamageToPlayer(u16 damage) {
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

void ApplyPiranhaArmyDoubleDirectDamage(void) {
  u16 damage;

  if (sActionData.id == 4 && sActionData.playerCardId == PIRANHA_ARMY) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage > 0)
      ApplyDirectDamageToOpponent(sActionData.playerCardAtkOrLifePointsMod);
    return;
  }

  if (sActionData.id == 6 && sActionData.opponentCardId == PIRANHA_ARMY) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage > 0)
      ApplyDirectDamageToPlayer(sActionData.opponentCardAtkOrLifePointsMod);
  }
}
