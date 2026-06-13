#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "guardian_angel_joan.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct GuardianAngelJoanActionData {
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

extern struct GuardianAngelJoanActionData sActionData;

void ClearGuardianAngelJoanPending(void) {
  gPendingGuardianAngelJoanDuelist = GUARDIAN_ANGEL_JOAN_PENDING_NONE;
  gPendingGuardianAngelJoanDestroyedAtk = 0;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u16 GetOriginalCardAtk(u16 cardId) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static void MarkPendingGain(u8 duelist, u16 destroyedCardId) {
  u16 destroyedAtk = GetOriginalCardAtk(destroyedCardId);

  if (destroyedAtk == 0)
    return;

  gPendingGuardianAngelJoanDuelist = duelist;
  gPendingGuardianAngelJoanDestroyedAtk = destroyedAtk;
}

void ResolveGuardianAngelJoanBattleEffect(void) {
  u8 duelist;
  u16 destroyedAtk;

  duelist = gPendingGuardianAngelJoanDuelist;
  if (duelist == GUARDIAN_ANGEL_JOAN_PENDING_NONE)
    return;

  destroyedAtk = gPendingGuardianAngelJoanDestroyedAtk;
  ClearGuardianAngelJoanPending();

  if (duelist == DUEL_PLAYER)
    SetPlayerLifePointsToAdd(destroyedAtk);
  else
    SetOpponentLifePointsToAdd(destroyedAtk);

  HandleAtkAndLifePointsAction();

  gCardEffectTextData.cardId = GUARDIAN_ANGEL_JOAN;
  ActivateCardEffectText();
}

void ApplyGuardianAngelJoanBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == GUARDIAN_ANGEL_JOAN
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingGain(DUEL_PLAYER, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == GUARDIAN_ANGEL_JOAN
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingGain(DUEL_OPPONENT, sActionData.playerCardId);
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveGuardianAngelJoanBattleEffect();
}
