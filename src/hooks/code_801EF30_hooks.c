#include "global.h"
#include "configs/runtime.h"
#include "duel_main.h"

void HandleWin(void);
extern struct Duelist* gUnk8E00B30[];

void IncreaseDeckCapacity(u32);
void AddCardDropsToShop(void);
void AddMoneyFromDuelVictory(void);
void DisplayMoneyRewardText(void);
int GetCardsDrawn(u8 arg0);
u16 sub_801FFE0(void);

static void AddRewardCardToTrunk__Replacement(void) {
  u8 i;
  if (gAnte == CARD_NONE)
    return;
  for (i = 0; i < 10 && i < gDuelData.unk2A; i++) {
    gDuelData.unk14[i] = sub_801FFE0();
    AddCardQtyToTrunk(gDuelData.unk14[i], 1);
  }
}

static u32 GetConfiguredCapacityReward(u32 baseReward) {
  switch (baseReward) {
    case 1:
      return gRuntimeConfig.repeatable_opponent_capacity_reward;
    case 3:
      return gRuntimeConfig.story_opponent_capacity_reward;
    default:
      return baseReward;
  }
}

LYN_REPLACE_CHECK(HandleWin);
void HandleWin__Replacement(void) {
  struct DuelText duelText;
  gDuelData.capacityYield = GetConfiguredCapacityReward(gUnk8E00B30[gDuelData.opponent]->capacityYield);
  IncreaseDeckCapacity(gDuelData.capacityYield);
  AddRewardCardToTrunk__Replacement();
  AddCardDropsToShop();
  AddMoneyFromDuelVictory();
  if (!gDuelLifePoints[DUEL_OPPONENT]) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_OPPONENT_OUT_OF_LP;
    DisplayDuelText(&duelText);
  }
  else if (NumCardsInDeck(1) < GetCardsDrawn(1)) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_OPPONENT_DECK_OUT;
    DisplayDuelText(&duelText);
  }
  if (gDuelData.unk2d) {
    u8 i;
    PlayMusic(gDuelData.winMusic);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_DUEL_VICTORY;
    DisplayDuelText(&duelText);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_CAPACITY_INCREASED;
    duelText.rewardAmount = gDuelData.capacityYield;
    DisplayDuelText(&duelText);
    DisplayMoneyRewardText();
    for (i = 0; i < 10; i++) {
      if (!gDuelData.unk14[i])
        break;
      ResetDuelTextData(&duelText);
      duelText.textId = DUEL_TEXT_CARD_OBTAINED;
      duelText.unk0 = gDuelData.unk14[i];
      DisplayDuelText(&duelText);
      SetCardInfo(gDuelData.unk14[i]);
      ShowCardDetailView();
    }
  }
  if (gDuelType == DUEL_TYPE_INGAME)
    CapLifePointsAfterDuel();
}
