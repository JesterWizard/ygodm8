#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "dragon_s_rage.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_OPPONENT 16
#define FLAG_LOSER_PLAYER 4

struct DragonsRageActionData {
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

extern struct DragonsRageActionData sActionData;
u8 CanMonsterBeDestroyedByBattle(u16 cardId, u8 fixedDuelist, u16 defStat, u16 atkStat);

static void ActivateDRAGON_S_RAGEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DRAGON_S_RAGE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateDRAGON_S_RAGEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DRAGON_S_RAGE, ActivateDRAGON_S_RAGEZone);
}

static u8 AttackerIsDragonWithRage(u8 attackerRow, u8 attackerCol)
{
  struct DuelCard *attacker = gFixedZones[attackerRow][attackerCol];
  u8 controller;

  if (attacker == NULL || attacker->id == CARD_NONE)
    return FALSE;
  if (!Duel_CardHasMonsterType(attacker->id, TYPE_DRAGON))
    return FALSE;

  controller = Duel_FixedDuelistForMonsterRow(attackerRow);
  return Duel_FindBackrowCard(controller, DRAGON_S_RAGE, TRUE) != NULL;
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

void ApplyDragonsRagePiercingBattleEffect(void)
{
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2
      && AttackerIsDragonWithRage(sActionData.playerMonsterRow, sActionData.unkA)) {
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
      && AttackerIsDragonWithRage(sActionData.opponentMonsterRow, sActionData.unk16)) {
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
