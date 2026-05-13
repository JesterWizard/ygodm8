#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

struct StoneUnk2023E80 {
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

extern struct StoneUnk2023E80 sActionData;

LYN_REPLACE_CHECK(CheckGraveyardAndLoserFlags);
void CheckGraveyardAndLoserFlags__Replacement(void) {
  u16 damage;

  if (sActionData.playerCardId == STONE_STATUE_OF_THE_AZTECS && sActionData.id == 5) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage > 0) {
      if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
        gDuelLifePoints[DUEL_OPPONENT] = 0;
        sActionData.flags |= 16;
      } else {
        gDuelLifePoints[DUEL_OPPONENT] -= damage;
      }
      gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    }
  }

  if (sActionData.opponentCardId == STONE_STATUE_OF_THE_AZTECS && sActionData.id == 2) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage > 0) {
      if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
        gDuelLifePoints[DUEL_PLAYER] = 0;
        sActionData.flags |= 4;
      } else {
        gDuelLifePoints[DUEL_PLAYER] -= damage;
      }
      gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    }
  }

  if (sActionData.flags & 1)
    ClearZoneAndSendMonToGraveyard2(gFixedZones[sActionData.playerMonsterRow][sActionData.unkA], 0);
  if (sActionData.flags & 2)
    ClearZoneAndSendMonToGraveyard2(gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16], 1);
  if (sActionData.flags & 4)
    DeclareLoser(0);
  if (sActionData.flags & 16)
    DeclareLoser(1);
}
