#include "global.h"
#include "common-chax.h"
#include "big_bang_shot.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct BigBangShotActionData {
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

extern struct BigBangShotActionData sActionData;

static u8 AttackerHasBigBangShot(u8 attackerRow, u8 attackerCol)
{
  struct DuelCard *attacker;

  attacker = gFixedZones[attackerRow][attackerCol];
  if (attacker == NULL || attacker->id == CARD_NONE)
    return FALSE;

  return DynamicEquipTargetsMonsterWithSpell(attacker, BIG_BANG_SHOT);
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

void ApplyBigBangShotPiercingBattleEffect(void)
{
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2
      && AttackerHasBigBangShot(sActionData.playerMonsterRow, sActionData.unkA)) {
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    if (attackerAtk <= defenderDef)
      return;

    if (CanMonsterBeDestroyedByBattle(
            sActionData.opponentCardId, DUEL_OPPONENT,
            sActionData.opponentCardAtkOrLifePointsMod,
            sActionData.playerCardAtkOrLifePointsMod))
      sActionData.flags |= FLAG_GRAVEYARD_OPPONENT;

    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToOpponent(damage);
    return;
  }

  if (sActionData.id == 5
      && AttackerHasBigBangShot(sActionData.opponentMonsterRow, sActionData.unk16)) {
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    if (attackerAtk <= defenderDef)
      return;

    if (CanMonsterBeDestroyedByBattle(
            sActionData.playerCardId, DUEL_PLAYER,
            sActionData.playerCardAtkOrLifePointsMod,
            sActionData.opponentCardAtkOrLifePointsMod))
      sActionData.flags |= FLAG_GRAVEYARD_PLAYER;

    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToPlayer(damage);
  }
}
