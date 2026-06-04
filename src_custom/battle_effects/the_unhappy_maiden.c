#include "global.h"
#include "common-chax.h"
#include "the_unhappy_maiden.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct UnhappyMaidenActionData {
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

extern struct UnhappyMaidenActionData sActionData;
extern unsigned char gIsPlayerTurnOver;

void EndActiveDuelistTurn(void) {
  if (WhoseTurn() == DUEL_PLAYER)
    gIsPlayerTurnOver = TRUE;
  else
    gForceActiveTurnEnd = TRUE;
}

void ResolveTheUnhappyMaidenBattleEffect(void) {
  u8 pending;

  pending = gPendingUnhappyMaiden;
  if (pending == 0)
    return;

  gPendingUnhappyMaiden = 0;

  gCardEffectTextData.cardId = THE_UNHAPPY_MAIDEN;
  ActivateCardEffectText();

  if (pending & UNHAPPY_MAIDEN_PENDING_PLAYER)
    GetGraveCardAndClearGrave2(DUEL_PLAYER);
  if (pending & UNHAPPY_MAIDEN_PENDING_OPPONENT)
    GetGraveCardAndClearGrave2(DUEL_OPPONENT);

  EndActiveDuelistTurn();
}

void ApplyTheUnhappyMaidenBattleEffect(void) {
  u8 playerSent;
  u8 opponentSent;

  playerSent = (sActionData.flags & FLAG_GRAVEYARD_PLAYER) != 0
      && gDuel.duelistbattleState[DUEL_PLAYER].graveyard == THE_UNHAPPY_MAIDEN;
  opponentSent = (sActionData.flags & FLAG_GRAVEYARD_OPPONENT) != 0
      && gDuel.duelistbattleState[DUEL_OPPONENT].graveyard == THE_UNHAPPY_MAIDEN;

  if (!playerSent && !opponentSent)
    return;

  /* AI_Main simulates attacks with gHideEffectText set; duel state is restored
   * after each trial but gForceActiveTurnEnd is not, which would end the turn early. */
  if (gHideEffectText)
    return;

  if (playerSent)
    gPendingUnhappyMaiden |= UNHAPPY_MAIDEN_PENDING_PLAYER;
  if (opponentSent)
    gPendingUnhappyMaiden |= UNHAPPY_MAIDEN_PENDING_OPPONENT;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveTheUnhappyMaidenBattleEffect();
}
