#include "global.h"
#include "constants/card_ids.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "the_dark_door.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct BlsEnvoyActionData {
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

extern struct BlsEnvoyActionData sActionData;

void TryUnlockBlackLusterSoldierEnvoyForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->id != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn != FALSE)
    return;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 2) {
    if (sActionData.playerCardId != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
      return;
  } else {
    if (sActionData.opponentCardId != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_PLAYER))
      return;
  }

  attacker->effectUsedThisTurn = TRUE;
  attacker->isLocked = FALSE;
}
