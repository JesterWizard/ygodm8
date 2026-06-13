#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "sasuke_samurai.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct SasukeSamuraiActionData {
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

extern struct SasukeSamuraiActionData sActionData;

static u8 sDefenderWasFaceDown APPEND_DATA = FALSE;

void HandleAtkAndLifePointsAction(void);

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 5;
}

static void SyncActionDataToBattleLog(void) {
  gDuelLifePoints[sActionData.unk1A] = sActionData.playerLifePoints;
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = sActionData.playerLifePoints;
  gDuelLifePoints[sActionData.unk1B] = sActionData.opponentLifePoints;
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = sActionData.opponentLifePoints;
  gUnk2023EA0.unk0[0].cardId = sActionData.playerCardId;
  gUnk2023EA0.unk0[0].cardAttribute = sActionData.playerCardAttribute;
  gUnk2023EA0.unk0[0].cardAttack = sActionData.playerCardAtkOrLifePointsMod;
  gUnk2023EA0.unk0[0].cardDefense = sActionData.playerCardDefense;
  gUnk2023EA0.unk0[1].cardId = sActionData.opponentCardId;
  gUnk2023EA0.unk0[1].cardAttribute = sActionData.opponentCardAttribute;
  gUnk2023EA0.unk0[1].cardAttack = sActionData.opponentCardAtkOrLifePointsMod;
  gUnk2023EA0.unk0[1].cardDefense = sActionData.opponentCardDefense;
}

static u8 DefenderWasFaceDownForPendingAttack(void) {
  struct DuelCard *defender;

  if (sDefenderWasFaceDown)
    return TRUE;

  if (!IsMonsterBattleAction(sActionData.id))
    return FALSE;

  if (sActionData.id == 1 || sActionData.id == 2) {
    defender = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    return defender->id != CARD_NONE && !defender->isFaceUp;
  }

  if (sActionData.id == 5) {
    defender = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    return defender->id != CARD_NONE && !defender->isFaceUp;
  }

  return FALSE;
}

void RefreshPendingSasukeBattleTarget(void) {
  struct DuelCard *defender;

  if (gDuelCursor.state != 4 || gDuelCursor.currentY != OPPONENT_MONSTER_ROW)
    return;

  defender = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];
  if (defender->id == CARD_NONE) {
    sDefenderWasFaceDown = FALSE;
    return;
  }

  sDefenderWasFaceDown = !defender->isFaceUp;
}

u8 TryHandleSasukeSamuraiFaceDownAttack(void) {
  struct DuelCard *attacker;

  if (!DefenderWasFaceDownForPendingAttack())
    return FALSE;

  sDefenderWasFaceDown = FALSE;

  if ((sActionData.id == 1 || sActionData.id == 2)
      && sActionData.playerCardId == SASUKE_SAMURAI) {
    attacker = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (attacker->id != SASUKE_SAMURAI)
      return FALSE;

    sActionData.flags = FLAG_GRAVEYARD_OPPONENT;
    gUnk2023EA0.unk18 = 16;
    SyncActionDataToBattleLog();
    return TRUE;
  }

  if (sActionData.id == 5 && sActionData.opponentCardId == SASUKE_SAMURAI) {
    attacker = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (attacker->id != SASUKE_SAMURAI)
      return FALSE;

    sActionData.flags = FLAG_GRAVEYARD_PLAYER;
    gUnk2023EA0.unk18 = 9;
    SyncActionDataToBattleLog();
    return TRUE;
  }

  return FALSE;
}

void RunMonsterBattleAction(void) {
  if (!TryHandleSasukeSamuraiFaceDownAttack())
    HandleAtkAndLifePointsAction();
}
