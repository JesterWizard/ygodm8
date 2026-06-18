#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "royal_knight.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct RoyalKnightActionData {
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

extern struct RoyalKnightActionData sActionData;

void ClearRoyalKnightPending(void) {
  gPendingRoyalKnightDuelist = ROYAL_KNIGHT_PENDING_NONE;
  gPendingRoyalKnightDestroyedDef = 0;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u16 GetOriginalCardDef(u16 cardId) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].def;
}

static void MarkPendingGain(u8 duelist, u16 destroyedCardId) {
  u16 destroyedDef = GetOriginalCardDef(destroyedCardId);

  if (destroyedDef == 0)
    return;

  gPendingRoyalKnightDuelist = duelist;
  gPendingRoyalKnightDestroyedDef = destroyedDef;
}

void ResolveRoyalKnightBattleEffect(void) {
  u8 duelist;
  u16 destroyedDef;

  duelist = gPendingRoyalKnightDuelist;
  if (duelist == ROYAL_KNIGHT_PENDING_NONE)
    return;

  Duel_ShowEffectTextTyped(ROYAL_KNIGHT, 3);

  destroyedDef = gPendingRoyalKnightDestroyedDef;
  ClearRoyalKnightPending();

  if (Duel_ChangeLp(duelist, destroyedDef, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

}

void ApplyRoyalKnightBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ROYAL_KNIGHT
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingGain(DUEL_PLAYER, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == ROYAL_KNIGHT
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingGain(DUEL_OPPONENT, sActionData.playerCardId);
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveRoyalKnightBattleEffect();
}
