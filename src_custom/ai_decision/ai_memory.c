#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "duel.h"

extern struct AiDuelMemory gAiDuelMemory;

void AiMemory_Reset(void) {
  u8 col;

  gAiDuelMemory.lastActionIndex = 0xFFFF;
  gAiDuelMemory.lastHandCol = 0xFF;
  gAiDuelMemory.lastActionCategory = AI_CATEGORY_NONE;
  gAiDuelMemory.opponentTurnCount = 0;
  gAiDuelMemory.blockedActionMask = 0;
  gAiDuelMemory.turnAttackCount = 0;
  gAiDuelMemory.attackOrderSalt = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    gAiDuelMemory.lastKnownFaceUp[col] = CARD_NONE;
    gAiDuelMemory.seenMonsters[col].cardId = CARD_NONE;
    gAiDuelMemory.seenMonsters[col].column = col;
    gAiDuelMemory.seenMonsters[col].valid = 0;
  }
}

void AiMemory_NotifyBlockedTribute(void) {
  gAiDuelMemory.blockedActionMask |= 1;
}

void AiMemory_OnOpponentTurnStart(void) {
  gAiDuelMemory.opponentTurnCount++;
  gAiDuelMemory.turnAttackCount = 0;
  gAiDuelMemory.attackOrderSalt =
      (gAiDuelMemory.attackOrderSalt + 13 + gAiDuelMemory.opponentTurnCount) & 7;
}

void AiMemory_RefreshBoardKnowledge(void) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (card->id == CARD_NONE) {
      gAiDuelMemory.lastKnownFaceUp[col] = CARD_NONE;
      gAiDuelMemory.seenMonsters[col].valid = 0;
      continue;
    }

    if (card->isFaceUp) {
      gAiDuelMemory.lastKnownFaceUp[col] = card->id;
      gAiDuelMemory.seenMonsters[col].valid = 0;
    } else if (gAiDuelMemory.lastKnownFaceUp[col] != CARD_NONE) {
      gAiDuelMemory.seenMonsters[col].cardId = gAiDuelMemory.lastKnownFaceUp[col];
      gAiDuelMemory.seenMonsters[col].column = col;
      gAiDuelMemory.seenMonsters[col].valid = 1;
    }
  }
}

void AiMemory_RecordExecutedAction(void) {
  struct AiDecodedAction decoded;

  AiDecodeActionIndex(g2021BF8, &decoded);
  gAiDuelMemory.lastActionIndex = decoded.actionIndex;
  gAiDuelMemory.lastHandCol = decoded.handCol;
  gAiDuelMemory.lastActionCategory = decoded.category;

  if (decoded.category == AI_CATEGORY_ATTACK || decoded.category == AI_CATEGORY_DIRECT)
    gAiDuelMemory.turnAttackCount++;
}
