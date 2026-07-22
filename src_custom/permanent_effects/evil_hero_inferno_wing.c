#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_inferno_wing.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct InfernoWingActionData {
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

extern struct InfernoWingActionData sActionData;

static u16 MaxAtkOrDef(u16 cardId)
{
  u16 atk;
  u16 def;

  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  atk = gCardData_NEW[cardId].atk;
  def = gCardData_NEW[cardId].def;
  return atk > def ? atk : def;
}

static void BurnOpponent(u16 damage)
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

static void BurnPlayer(u16 damage)
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

void ApplyEvilHeroInfernoWingBattleEffect(void)
{
  u16 burn;

  if (sActionData.playerCardId == EVIL_HERO_INFERNO_WING
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    burn = MaxAtkOrDef(sActionData.opponentCardId);
    if (burn != 0) {
      Duel_ShowEffectTextTyped(EVIL_HERO_INFERNO_WING, 2);
      BurnOpponent(burn);
    }
    return;
  }

  if (sActionData.opponentCardId == EVIL_HERO_INFERNO_WING
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    burn = MaxAtkOrDef(sActionData.playerCardId);
    if (burn != 0) {
      Duel_ShowEffectTextTyped(EVIL_HERO_INFERNO_WING, 2);
      BurnPlayer(burn);
    }
  }
}

unsigned char ShouldActivateEVIL_HERO_INFERNO_WING(void)
{
  /* Pierce via ApplySimplePiercersBattleEffect;
   * battle-destroy burn via ApplyEvilHeroInfernoWingBattleEffect. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNO_WING(void)
{
}
