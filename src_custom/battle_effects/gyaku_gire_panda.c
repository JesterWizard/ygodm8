#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "gyaku_gire_panda.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct GyakuGirePandaActionData {
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

extern struct GyakuGirePandaActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static void ApplyPiercingDamageToOpponent(u16 damage)
{
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

static void ApplyPiercingDamageToPlayer(u16 damage)
{
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

static void ApplyGyakuGirePandaPiercingDamage(void)
{
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2 && sActionData.playerCardId == GYAKU_GIRE_PANDA) {
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

  if (sActionData.id == 5 && sActionData.opponentCardId == GYAKU_GIRE_PANDA) {
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

void ApplyGyakuGirePandaBattleEffect(void)
{
  if (sActionData.playerCardId != GYAKU_GIRE_PANDA && sActionData.opponentCardId != GYAKU_GIRE_PANDA)
    return;
  if (!IsMonsterBattleAction(sActionData.id))
    return;

  ApplyGyakuGirePandaPiercingDamage();
}
