#ifndef GUARD_AI_DECISION_H
#define GUARD_AI_DECISION_H

#include "gba/types.h"
#include "duel.h"

#define AI_PRIORITY_DISABLE 0x7EDE89F9
#define AI_PRIORITY_LETHAL_MIN 0x7FFFFFF0
#define AI_MAX_EVALUATED_ACTIONS 0x3B2
#define AI_SMART_VARIANCE_MARGIN 0x15000u
#define AI_SMART_FILTER_MARGIN   0x25000u

#define AI_MOD_DELTA_MAX 0x8000u
#define AI_MOD_DELTA_MIN 0x2000u

enum AiActionCategory {
  AI_CATEGORY_NONE,
  AI_CATEGORY_ATTACK,
  AI_CATEGORY_DIRECT,
  AI_CATEGORY_SUMMON,
  AI_CATEGORY_DEFENSE,
  AI_CATEGORY_SET_SPELL,
  AI_CATEGORY_SET_TRAP,
  AI_CATEGORY_ACTIVATE_SPELL,
  AI_CATEGORY_ACTIVATE_TRAP,
  AI_CATEGORY_MONSTER_EFFECT,
  AI_CATEGORY_OTHER,
};

struct AiActionTemplate {
  u16 action;
  u8 zones[6];
};

struct AiActionPriorityEntry {
  u16 actionIndex;
  u32 priority;
};

struct AiActionPriorityTable {
  u8 _before[0x504];
  struct AiActionPriorityEntry entries[AI_MAX_EVALUATED_ACTIONS];
  u16 actionCount;
};

struct AiDecodedAction {
  u16 actionIndex;
  u16 action;
  u8 category;
  u8 handCol;
  u8 zone0Row;
  u8 zone0Col;
  u8 zone1Row;
  u8 zone1Col;
  u16 primaryCardId;
  u16 secondaryCardId;
};

struct AiSeenFaceDownMonster {
  u16 cardId;
  u8 column;
  u8 valid;
};

struct AiDuelMemory {
  u16 lastActionIndex;
  u8 lastHandCol;
  u8 lastActionCategory;
  u8 opponentTurnCount;
  u8 blockedActionMask;
  u8 turnAttackCount;
  u8 attackOrderSalt;
  u16 lastKnownFaceUp[MAX_ZONES_IN_ROW];
  struct AiSeenFaceDownMonster seenMonsters[MAX_ZONES_IN_ROW];
};

struct AiDecisionContext {
  struct AiActionPriorityEntry *entries;
  u16 actionCount;
  u16 aiLifePoints;
  u16 playerLifePoints;
  s16 lifePointDelta;
  u8 opponentTurnCount;
  u8 hasLethalLine;
  u8 playerHasSetBackrow;
  u8 hasBeatableFaceUpTarget;
  u16 weakestAttackerAtk;
  u16 strongestAttackerAtk;
  u8 visibleHandThreat;
  u8 visibleHandHasMonster;
  u8 visibleHandHasTrapOrSpell;
  u8 preferredEmptyMonsterCol;
  u8 preferredEmptyBackrowCol;
};

extern struct AiActionPriorityTable *gUnk_8DFF6A4;
extern struct AiDuelMemory gAiDuelMemory;

u16 AiDecision_PickAction(void);
void AiMemory_Reset(void);
void AiApplyModifiers(struct AiDecisionContext *ctx);
void AiTactics_FillContext(struct AiDecisionContext *ctx);

u8 AiTactics_ActionDestroysFaceUpMonster(u16 actionIndex);
u8 AiTactics_ActionDealsFaceUpBattleDamage(u16 actionIndex);
u8 AiTactics_HasValidDestroyFaceUpLine(
    struct AiActionPriorityEntry *entries, u16 actionCount);
u8 AiTactics_ShouldForceDestroyFaceUp(const struct AiDecisionContext *ctx);

void AiDecodeActionIndex(u16 actionIndex, struct AiDecodedAction *out);
u8 AiAction_GetCategory(u16 action);
u16 AiAction_GetCardAtZone(u8 zonePosition);
u8 AiAction_IsHighImpact(u16 action);

void AiMemory_OnOpponentTurnStart(void);
void AiMemory_NotifyBlockedTribute(void);
void AiMemory_RecordExecutedAction(void);
void AiMemory_RefreshBoardKnowledge(void);

#endif
