#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "absorbing_kid_from_the_sky.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define ABSORBING_KID_FROM_THE_SKY_LP_PER_LEVEL 300

struct AbsorbingKidFromTheSkyActionData {
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

extern struct AbsorbingKidFromTheSkyActionData sActionData;

void ClearAbsorbingKidFromTheSkyPending(void) {
  gPendingAbsorbingKidFromTheSkyDuelist = ABSORBING_KID_FROM_THE_SKY_PENDING_NONE;
  gPendingAbsorbingKidFromTheSkyLevel = 0;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 GetDestroyedMonsterLevel(u16 destroyedCardId) {
  if (destroyedCardId == CARD_NONE || destroyedCardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[destroyedCardId].level;
}

static void MarkPendingGain(u8 duelist, u16 destroyedCardId) {
  u8 level = GetDestroyedMonsterLevel(destroyedCardId);

  if (level == 0)
    return;

  gPendingAbsorbingKidFromTheSkyDuelist = duelist;
  gPendingAbsorbingKidFromTheSkyLevel = level;
}

void ResolveAbsorbingKidFromTheSkyBattleEffect(void) {
  u8 duelist;
  u8 level;
  u16 heal;

  duelist = gPendingAbsorbingKidFromTheSkyDuelist;
  if (duelist == ABSORBING_KID_FROM_THE_SKY_PENDING_NONE)
    return;

  level = gPendingAbsorbingKidFromTheSkyLevel;
  ClearAbsorbingKidFromTheSkyPending();

  if (level == 0)
    return;

  heal = (u16)level * ABSORBING_KID_FROM_THE_SKY_LP_PER_LEVEL;

  if (duelist == DUEL_PLAYER)
    SetPlayerLifePointsToAdd(heal);
  else
    SetOpponentLifePointsToAdd(heal);

  HandleAtkAndLifePointsAction();

  gCardEffectTextData.cardId = ABSORBING_KID_FROM_THE_SKY;
  ActivateCardEffectText();
}

void ApplyAbsorbingKidFromTheSkyBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ABSORBING_KID_FROM_THE_SKY
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingGain(DUEL_PLAYER, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == ABSORBING_KID_FROM_THE_SKY
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingGain(DUEL_OPPONENT, sActionData.playerCardId);
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveAbsorbingKidFromTheSkyBattleEffect();
}
