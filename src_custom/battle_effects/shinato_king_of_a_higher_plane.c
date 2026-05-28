#include "global.h"
#include "common-chax.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct ShinatoActionData {
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

extern struct ShinatoActionData sActionData;

void ApplyShinatoKingOfAHigherPlaneBattleEffect(void) {
  u16 destroyedCardId;
  u16 damage;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 2) {
    if (sActionData.playerCardId != SHINATO_KING_OF_A_HIGHER_PLANE)
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
      return;
    destroyedCardId = sActionData.opponentCardId;
    damage = gCardAtks[destroyedCardId];
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
    return;
  }

  if (sActionData.opponentCardId != SHINATO_KING_OF_A_HIGHER_PLANE)
    return;
  if (!(sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    return;
  destroyedCardId = sActionData.playerCardId;
  damage = gCardAtks[destroyedCardId];
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
