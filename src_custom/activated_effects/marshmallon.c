#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "marshmallon.h"

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16
#define MARSHMALLON_FLIP_BURN 1000

struct MarshmallonActionData {
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

extern struct MarshmallonActionData sActionData;

static void BurnOpponent(void)
{
  if (gDuelLifePoints[DUEL_OPPONENT] <= MARSHMALLON_FLIP_BURN) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= MARSHMALLON_FLIP_BURN;
  }
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void BurnPlayer(void)
{
  if (gDuelLifePoints[DUEL_PLAYER] <= MARSHMALLON_FLIP_BURN) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= MARSHMALLON_FLIP_BURN;
  }
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

void ApplyMarshmallonBattleEffect(void)
{
  /* id 2/5 ≈ DEF-position attack (face-down Set stand-in). */
  if (sActionData.id == 2 && sActionData.opponentCardId == MARSHMALLON) {
    Duel_ShowEffectTextTyped(MARSHMALLON, 2);
    BurnOpponent();
    return;
  }

  if (sActionData.id == 5 && sActionData.playerCardId == MARSHMALLON) {
    Duel_ShowEffectTextTyped(MARSHMALLON, 2);
    BurnPlayer();
  }
}

unsigned char CanActivateMARSHMALLON(void)
{
  if (gMonEffect.id != MARSHMALLON)
    return FALSE;

  /* Battle destroy immunity via CanMonsterBeDestroyedByBattle;
   * flip-attack burn via ApplyMarshmallonBattleEffect. */
  return FALSE;
}

void ActivateMARSHMALLONEffect(void)
{
  Duel_ShowEffectTextTyped(MARSHMALLON, 2);
}
