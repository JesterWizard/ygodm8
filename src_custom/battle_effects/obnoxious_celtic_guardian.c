#include "global.h"
#include "common-chax.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define OCG_ATK_THRESHOLD 1900

struct ObnoxiousCelticGuardianActionData {
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

extern struct ObnoxiousCelticGuardianActionData sActionData;

void ApplyObnoxiousCelticGuardianBattleProtection(void) {
  if (sActionData.playerCardId == OBNOXIOUS_CELTIC_GUARDIAN
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.opponentCardAtkOrLifePointsMod >= OCG_ATK_THRESHOLD) {
    sActionData.flags &= ~FLAG_GRAVEYARD_PLAYER;
  }

  if (sActionData.opponentCardId == OBNOXIOUS_CELTIC_GUARDIAN
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.playerCardAtkOrLifePointsMod >= OCG_ATK_THRESHOLD) {
    sActionData.flags &= ~FLAG_GRAVEYARD_OPPONENT;
  }
}
