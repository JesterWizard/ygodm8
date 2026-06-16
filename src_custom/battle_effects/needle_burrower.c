#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "needle_burrower.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define NEEDLE_BURROWER_DAMAGE_PER_LEVEL 500

struct NeedleBurrowerActionData {
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

extern struct NeedleBurrowerActionData sActionData;

void ClearNeedleBurrowerPending(void) {
  gPendingNeedleBurrowerController = NEEDLE_BURROWER_PENDING_NONE;
  gPendingNeedleBurrowerLevel = 0;
}

static u8 IsBattleDestroyBurner(u16 cardId) {
  return cardId == NEEDLE_BURROWER || cardId == DES_SCISSORS;
}

static u16 BattleDestroyBurnerEffectCard(u8 controller) {
  u16 cardId = controller == DUEL_PLAYER
      ? sActionData.playerCardId
      : sActionData.opponentCardId;

  return IsBattleDestroyBurner(cardId) ? cardId : NEEDLE_BURROWER;
}

static u8 GetDestroyedMonsterLevel(u16 destroyedCardId) {
  if (destroyedCardId == CARD_NONE || destroyedCardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[destroyedCardId].level;
}

static void MarkPendingDamage(u8 controller, u16 destroyedCardId) {
  u8 level = GetDestroyedMonsterLevel(destroyedCardId);

  if (level == 0)
    return;

  gPendingNeedleBurrowerController = controller;
  gPendingNeedleBurrowerLevel = level;
}

void ResolveNeedleBurrowerBattleEffect(void) {
  u8 controller;
  u8 level;
  u16 damage;

  controller = gPendingNeedleBurrowerController;
  if (controller == NEEDLE_BURROWER_PENDING_NONE)
    return;

  level = gPendingNeedleBurrowerLevel;
  ClearNeedleBurrowerPending();

  if (level == 0)
    return;

  damage = (u16)level * NEEDLE_BURROWER_DAMAGE_PER_LEVEL;

  if (Duel_ChangeLp(controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER, -(s32)damage, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(BattleDestroyBurnerEffectCard(controller), 3);
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

void ApplyNeedleBurrowerBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (IsBattleDestroyBurner(sActionData.playerCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingDamage(DUEL_PLAYER, sActionData.opponentCardId);
  } else if (IsBattleDestroyBurner(sActionData.opponentCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingDamage(DUEL_OPPONENT, sActionData.playerCardId);
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveNeedleBurrowerBattleEffect();
}
