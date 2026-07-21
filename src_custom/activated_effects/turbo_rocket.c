#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "turbo_rocket.h"

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct TurboRocketActionData {
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

extern struct TurboRocketActionData sActionData;

static void ApplyBurnBoth(u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }

  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }

  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

void ApplyTurboRocketBattleEffect(void)
{
  u16 battledAtk = 0;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == TURBO_ROCKET)
    battledAtk = sActionData.opponentCardAtkOrLifePointsMod;
  else if (sActionData.opponentCardId == TURBO_ROCKET)
    battledAtk = sActionData.playerCardAtkOrLifePointsMod;
  else
    return;

  Duel_ShowEffectTextTyped(TURBO_ROCKET, 2);
  ApplyBurnBoth(battledAtk / 2);
}

unsigned char CanActivateTURBO_ROCKET(void)
{
  if (gMonEffect.id != TURBO_ROCKET)
    return FALSE;

  /* Battle destroy immunity via CanMonsterBeDestroyedByBattle;
   * post-battle burn via ApplyTurboRocketBattleEffect. */
  return FALSE;
}

void ActivateTURBO_ROCKETEffect(void)
{
  Duel_ShowEffectTextTyped(TURBO_ROCKET, 2);
}
