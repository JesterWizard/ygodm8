#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "simple_piercers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct SimplePiercerActionData {
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

extern struct SimplePiercerActionData sActionData;

static const u16 sPiercerIds[] APPEND_RODATA = {
  ENRAGED_BATTLE_OX,
  GRAVEKEEPERS_SPEAR_SOLDIER,
};

static u8 IsListedPiercer(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sPiercerIds); i++) {
    if (sPiercerIds[i] == cardId)
      return TRUE;
  }
  return FALSE;
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

void ApplySimplePiercersBattleEffect(void)
{
  u16 atk;
  u16 def;

  if (sActionData.id == 2 && IsListedPiercer(sActionData.playerCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    atk = sActionData.playerCardAtkOrLifePointsMod;
    def = sActionData.opponentCardDefense;
    if (atk > def)
      ApplyPiercingDamageToOpponent(atk - def);
    return;
  }

  if (sActionData.id == 5 && IsListedPiercer(sActionData.opponentCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    atk = sActionData.opponentCardAtkOrLifePointsMod;
    def = sActionData.playerCardDefense;
    if (atk > def)
      ApplyPiercingDamageToPlayer(atk - def);
  }
}
