#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_helpers.h"

static void AiMod_ApplyDelta(u32 *priority, s32 delta) {
  if (*priority == 0 || *priority == AI_PRIORITY_DISABLE)
    return;
  if (*priority >= AI_PRIORITY_LETHAL_MIN)
    return;

  if (delta >= 0) {
    *priority += (u32)delta;
  } else if ((u32)(-delta) < *priority) {
    *priority -= (u32)(-delta);
  } else {
    *priority = 1;
  }
}

static u8 AiMod_IsFaceUpAttackAction(u16 action) {
  return IsAiFaceUpAttackAction(action);
}

static u16 AiMod_GetAttackerAtk(const struct AiDecodedAction *decoded) {
  struct DuelCard *attacker;
  u16 atk;
  u16 def;
  u8 attr;

  if (decoded->zone0Row != ACTIVE_DUELIST_MONSTER_ROW)
    return 0;

  attacker = gTurnZones[decoded->zone0Row][decoded->zone0Col];
  if (attacker->id == CARD_NONE)
    return 0;

  gStatMod.card = attacker->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(attacker);
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;
  def = gCardInfo.def;
  attr = gCardInfo.attribute;
  (void)def;
  (void)attr;
  return atk;
}

static u8 AiMod_AttackerBeatsDefenderAt(
    u8 attackerRow, u8 attackerCol, u8 defenderRow, u8 defenderCol) {
  struct DuelCard *attacker;
  struct DuelCard *defender;
  u16 atkAtt;
  u16 defAtt;
  u16 atkDef;
  u16 defDef;
  u8 attrAtt;
  u8 attrDef;
  u8 matchup;

  if (attackerRow >= 5 || defenderRow >= 5)
    return FALSE;

  attacker = gTurnZones[attackerRow][attackerCol];
  defender = gTurnZones[defenderRow][defenderCol];

  if (attacker->id == CARD_NONE || defender->id == CARD_NONE)
    return FALSE;

  gStatMod.card = attacker->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(attacker);
  SetFinalStat(&gStatMod);
  atkAtt = gCardInfo.atk;
  defAtt = gCardInfo.def;
  attrAtt = gCardInfo.attribute;
  (void)defAtt;

  gStatMod.card = defender->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(defender);
  SetFinalStat(&gStatMod);
  atkDef = gCardInfo.atk;
  defDef = gCardInfo.def;
  attrDef = gCardInfo.attribute;

  if (defender->isDefending) {
    if (gRuntimeConfig.disable_element_system == TRUE)
      return atkAtt > defDef;
    matchup = sub_803FBCC(attrAtt, attrDef);
    if (matchup == 0)
      return TRUE;
    if (matchup == 2)
      return atkAtt > defDef;
    return atkAtt > defDef;
  }

  if (gRuntimeConfig.disable_element_system == TRUE)
    return atkAtt > atkDef;

  matchup = sub_803FBCC(attrAtt, attrDef);
  if (matchup == 0)
    return TRUE;
  if (matchup == 2)
    return atkAtt > atkDef;
  return atkAtt > atkDef;
}

static u8 AiMod_DefenderIsKnownFaceDown(u8 defenderCol) {
  if (defenderCol >= MAX_ZONES_IN_ROW)
    return FALSE;
  return gAiDuelMemory.seenMonsters[defenderCol].valid;
}

void AiMod_LpMood(struct AiDecisionContext *ctx, u16 actionIndex, u32 *priority) {
  struct AiDecodedAction decoded;
  s32 delta = 0;
  u32 magnitude = AI_MOD_DELTA_MIN;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (ctx->lifePointDelta <= -2000) {
    if (decoded.category == AI_CATEGORY_ATTACK ||
        decoded.category == AI_CATEGORY_DIRECT ||
        decoded.category == AI_CATEGORY_SUMMON)
      delta += (s32)magnitude;
  } else if (ctx->lifePointDelta >= 2000) {
    if (decoded.category == AI_CATEGORY_DEFENSE ||
        decoded.category == AI_CATEGORY_SET_SPELL ||
        decoded.category == AI_CATEGORY_SET_TRAP)
      delta += (s32)magnitude;
    if (decoded.category == AI_CATEGORY_ATTACK ||
        decoded.category == AI_CATEGORY_DIRECT)
      delta -= (s32)(magnitude / 2);
  }

  AiMod_ApplyDelta(priority, delta);
}

void AiMod_SetupBias(struct AiDecisionContext *ctx, u16 actionIndex, u32 *priority) {
  struct AiDecodedAction decoded;
  s32 delta = 0;

  if (ctx->opponentTurnCount > 2)
    return;

  if (ctx->preferredEmptyMonsterCol != 0xFF)
    return;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category == AI_CATEGORY_SET_SPELL ||
      decoded.category == AI_CATEGORY_SET_TRAP ||
      decoded.category == AI_CATEGORY_DEFENSE)
    delta += (s32)AI_MOD_DELTA_MIN;

  AiMod_ApplyDelta(priority, delta);
}

void AiMod_DuelMemory(struct AiDecisionContext *ctx, u16 actionIndex, u32 *priority) {
  struct AiDecodedAction decoded;

  (void)ctx;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (gAiDuelMemory.lastActionIndex != 0xFFFF &&
      actionIndex == gAiDuelMemory.lastActionIndex &&
      decoded.handCol == gAiDuelMemory.lastHandCol)
    AiMod_ApplyDelta(priority, -(s32)AI_MOD_DELTA_MIN);

  if (gAiDuelMemory.blockedActionMask != 0 &&
      IsAiTributeSummonAction(decoded.action))
    AiMod_ApplyDelta(priority, -(s32)(AI_MOD_DELTA_MIN / 2));
}

static u16 AiMod_HighestFaceUpThreatAtk(void) {
  u8 col;
  u16 maxAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *defender = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;
    u16 def;
    u8 attr;

    if (defender->id == CARD_NONE || !defender->isFaceUp)
      continue;

    gStatMod.card = defender->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(defender);
    SetFinalStat(&gStatMod);
    atk = gCardInfo.atk;
    def = gCardInfo.def;
    attr = gCardInfo.attribute;
    (void)def;
    (void)attr;

    if (defender->isDefending) {
      if (gCardInfo.def > maxAtk)
        maxAtk = gCardInfo.def;
    } else if (atk > maxAtk) {
      maxAtk = atk;
    }
  }

  return maxAtk;
}

static void AiMod_AttackTargeting(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  struct DuelCard *defender;
  u8 defenderFaceUp;
  s32 delta = 0;

  if (decoded->category != AI_CATEGORY_ATTACK)
    return;
  if (decoded->zone1Row != INACTIVE_DUELIST_MONSTER_ROW)
    return;

  defender = gTurnZones[decoded->zone1Row][decoded->zone1Col];
  if (defender->id == CARD_NONE)
    return;

  defenderFaceUp = defender->isFaceUp;

  if (defenderFaceUp &&
      AiMod_AttackerBeatsDefenderAt(
          decoded->zone0Row, decoded->zone0Col, decoded->zone1Row, decoded->zone1Col)) {
    u16 threatAtk = AiMod_HighestFaceUpThreatAtk();
    u16 defenderPower;

    delta += (s32)AI_MOD_DELTA_MIN;

    gStatMod.card = defender->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(defender);
    SetFinalStat(&gStatMod);
    defenderPower = defender->isDefending ? gCardInfo.def : gCardInfo.atk;
    if (threatAtk != 0 && defenderPower == threatAtk)
      delta += (s32)(AI_MOD_DELTA_MIN / 2);

    if (!CanMonsterBeDestroyedByBattle(defender->id, INACTIVE_DUELIST, 0, 0) && !defender->isDefending)
      delta += (s32)(AI_MOD_DELTA_MIN / 2);
  }

  if (ctx->hasBeatableFaceUpTarget) {
    if (defenderFaceUp && AiMod_IsFaceUpAttackAction(decoded->action))
      delta += (s32)(AI_MOD_DELTA_MIN / 2);
    if (!defenderFaceUp && IsAiFaceDownAttackAction(decoded->action))
      delta -= (s32)AI_MOD_DELTA_MIN;
  }

  if (!defenderFaceUp && AiMod_DefenderIsKnownFaceDown(decoded->zone1Col)) {
    if (AiMod_AttackerBeatsDefenderAt(
            decoded->zone0Row,
            decoded->zone0Col,
            decoded->zone1Row,
            decoded->zone1Col)) {
      delta += (s32)(AI_MOD_DELTA_MIN / 2);
    } else {
      delta -= (s32)(AI_MOD_DELTA_MIN / 2);
    }
  }

  AiMod_ApplyDelta(priority, delta);
}

static void AiMod_AttackOrder(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  u16 attackerAtk;
  s32 delta = 0;
  u8 defenderFaceDown;
  struct DuelCard *defender;

  if (decoded->category != AI_CATEGORY_ATTACK)
    return;
  if (decoded->zone0Row != ACTIVE_DUELIST_MONSTER_ROW)
    return;

  attackerAtk = AiMod_GetAttackerAtk(decoded);
  if (attackerAtk == 0)
    return;

  defender = NULL;
  defenderFaceDown = FALSE;
  if (decoded->zone1Row == INACTIVE_DUELIST_MONSTER_ROW) {
    defender = gTurnZones[decoded->zone1Row][decoded->zone1Col];
    if (defender->id != CARD_NONE)
      defenderFaceDown = !defender->isFaceUp;
  }

  if (ctx->playerHasSetBackrow && gAiDuelMemory.turnAttackCount == 0) {
    if (ctx->weakestAttackerAtk != 0 && attackerAtk == ctx->weakestAttackerAtk)
      delta += (s32)AI_MOD_DELTA_MIN;
    if (ctx->strongestAttackerAtk != 0 && attackerAtk == ctx->strongestAttackerAtk)
      delta -= (s32)(AI_MOD_DELTA_MIN / 2);
  } else if (defenderFaceDown &&
             ctx->weakestAttackerAtk != 0 &&
             ctx->strongestAttackerAtk != ctx->weakestAttackerAtk) {
    u8 salt = gAiDuelMemory.attackOrderSalt + decoded->zone0Col;

    if (attackerAtk == ctx->strongestAttackerAtk && (salt & 3) != 0)
      delta -= (s32)(AI_MOD_DELTA_MIN / 2);
    else if (attackerAtk != ctx->strongestAttackerAtk && (salt & 3) == 0)
      delta += (s32)(AI_MOD_DELTA_MIN / 4);
  }

  AiMod_ApplyDelta(priority, delta);
}

static s8 AiMod_BestBoardMatchup(void) {
  u8 aiCol;
  u8 playerCol;
  s8 bestScore = -8;

  for (aiCol = 0; aiCol < MAX_ZONES_IN_ROW; aiCol++) {
    struct DuelCard *aiCard = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][aiCol];
    u8 aiAttr;
    s8 score = 0;

    if (aiCard->id == CARD_NONE)
      continue;

    gStatMod.card = aiCard->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(aiCard);
    SetFinalStat(&gStatMod);
    aiAttr = gCardInfo.attribute;

    for (playerCol = 0; playerCol < MAX_ZONES_IN_ROW; playerCol++) {
      struct DuelCard *playerCard = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][playerCol];
      u8 playerAttr;
      u8 matchup;

      if (playerCard->id == CARD_NONE || !playerCard->isFaceUp)
        continue;

      gStatMod.card = playerCard->id;
      gStatMod.field = gDuel.field;
      gStatMod.stage = GetFinalStage(playerCard);
      SetFinalStat(&gStatMod);
      playerAttr = gCardInfo.attribute;

      if (gRuntimeConfig.disable_element_system == TRUE)
        continue;

      matchup = sub_803FBCC(aiAttr, playerAttr);
      if (matchup == 0)
        score++;
      else if (matchup == 2)
        score--;
    }

    if (score > bestScore)
      bestScore = score;
  }

  return bestScore;
}

static s8 AiMod_SummonMatchupScore(u16 cardId) {
  u8 playerCol;
  s8 score = 0;
  u8 summonAttr;

  if (cardId == CARD_NONE)
    return 0;

  SetCardInfo(cardId);
  summonAttr = gCardInfo.attribute;

  for (playerCol = 0; playerCol < MAX_ZONES_IN_ROW; playerCol++) {
    struct DuelCard *playerCard = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][playerCol];
    u8 playerAttr;
    u8 matchup;

    if (playerCard->id == CARD_NONE || !playerCard->isFaceUp)
      continue;

    gStatMod.card = playerCard->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(playerCard);
    SetFinalStat(&gStatMod);
    playerAttr = gCardInfo.attribute;

    if (gRuntimeConfig.disable_element_system == TRUE)
      continue;

    matchup = sub_803FBCC(summonAttr, playerAttr);
    if (matchup == 0)
      score++;
    else if (matchup == 2)
      score--;
  }

  return score;
}

static void AiMod_CountSummonTypeMatchups(
    u16 cardId, u8 *advantageCount, u8 *disadvantageCount) {
  u8 playerCol;
  u8 summonAttr;

  *advantageCount = 0;
  *disadvantageCount = 0;

  if (cardId == CARD_NONE || gRuntimeConfig.disable_element_system == TRUE)
    return;

  SetCardInfo(cardId);
  summonAttr = gCardInfo.attribute;

  for (playerCol = 0; playerCol < MAX_ZONES_IN_ROW; playerCol++) {
    struct DuelCard *playerCard = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][playerCol];
    u8 playerAttr;
    u8 matchup;

    if (playerCard->id == CARD_NONE || !playerCard->isFaceUp)
      continue;

    gStatMod.card = playerCard->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(playerCard);
    SetFinalStat(&gStatMod);
    playerAttr = gCardInfo.attribute;

    matchup = sub_803FBCC(summonAttr, playerAttr);
    if (matchup == 0)
      (*advantageCount)++;
    else if (matchup == 2)
      (*disadvantageCount)++;
  }
}

static void AiMod_TributeBoard(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  s8 currentScore;
  s8 summonScore;
  u8 advantageCount;
  u8 disadvantageCount;
  s32 delta = 0;

  (void)ctx;

  if (!IsAiTributeSummonAction(decoded->action))
    return;

  currentScore = AiMod_BestBoardMatchup();
  summonScore = AiMod_SummonMatchupScore(decoded->primaryCardId);
  AiMod_CountSummonTypeMatchups(
      decoded->primaryCardId, &advantageCount, &disadvantageCount);

  if (advantageCount >= 1 && disadvantageCount >= 1) {
    delta += (s32)AI_MOD_DELTA_MIN;
    if (currentScore <= 0)
      delta += (s32)(AI_MOD_DELTA_MIN / 2);
  } else if (advantageCount >= 1 && disadvantageCount == 0) {
    delta += (s32)(AI_MOD_DELTA_MIN / 2);
  }

  if (summonScore < currentScore) {
    if (!(advantageCount >= 1 && disadvantageCount >= 1))
      delta -= (s32)AI_MOD_DELTA_MIN;
  } else if (summonScore > currentScore) {
    delta += (s32)(AI_MOD_DELTA_MIN / 2);
  }

  if (summonScore < 0 && advantageCount == 0)
    delta -= (s32)(AI_MOD_DELTA_MIN / 2);

  AiMod_ApplyDelta(priority, delta);
}

static void AiMod_OpponentHandRead(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  s32 delta = 0;

  if (ctx->visibleHandThreat == 0)
    return;

  if (ctx->visibleHandHasTrapOrSpell) {
    if (decoded->category == AI_CATEGORY_SET_TRAP ||
        decoded->category == AI_CATEGORY_DEFENSE)
      delta += (s32)(AI_MOD_DELTA_MIN / 2);

    if (!ctx->playerHasSetBackrow &&
        (decoded->category == AI_CATEGORY_ATTACK ||
         decoded->category == AI_CATEGORY_DIRECT))
      delta += (s32)(AI_MOD_DELTA_MIN / 2);

    if (IsAiTributeSummonAction(decoded->action))
      delta -= (s32)(AI_MOD_DELTA_MIN / 4);
  }

  if (ctx->visibleHandHasMonster) {
    if (decoded->category == AI_CATEGORY_ATTACK ||
        decoded->category == AI_CATEGORY_SUMMON)
      delta += (s32)(ctx->visibleHandThreat / 8);

    if (decoded->category == AI_CATEGORY_SET_TRAP &&
        ctx->playerHasSetBackrow)
      delta += (s32)(AI_MOD_DELTA_MIN / 4);
  }

  AiMod_ApplyDelta(priority, delta);
}

static void AiMod_SummonQuality(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  s32 delta = 0;
  u16 atk;

  if (decoded->category != AI_CATEGORY_SUMMON)
    return;
  if (ctx->preferredEmptyMonsterCol == 0xFF)
    return;
  if (decoded->zone1Row != ACTIVE_DUELIST_MONSTER_ROW)
    return;
  if (decoded->zone1Col != ctx->preferredEmptyMonsterCol)
    return;
  if (decoded->primaryCardId == CARD_NONE)
    return;

  SetCardInfo(decoded->primaryCardId);
  atk = gCardInfo.atk;

  if (atk >= 2000)
    delta += (s32)AI_MOD_DELTA_MIN;
  else if (atk >= 1500)
    delta += (s32)(AI_MOD_DELTA_MIN / 2);
  else if (atk >= 1000)
    delta += (s32)(AI_MOD_DELTA_MIN / 4);

  AiMod_ApplyDelta(priority, delta);
}

static void AiMod_SetBackrowPlacement(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  s32 delta = 0;

  if (ctx->preferredEmptyBackrowCol == 0xFF)
    return;
  if (decoded->category != AI_CATEGORY_SET_SPELL &&
      decoded->category != AI_CATEGORY_SET_TRAP)
    return;
  if (decoded->zone1Row != ACTIVE_DUELIST_BACKROW)
    return;

  if (decoded->zone1Col == ctx->preferredEmptyBackrowCol)
    delta += (s32)(AI_MOD_DELTA_MIN / 2);
  else
    delta -= (s32)AI_MOD_DELTA_MIN;

  AiMod_ApplyDelta(priority, delta);
}

static void AiMod_WastefulLine(
    struct AiDecisionContext *ctx, const struct AiDecodedAction *decoded, u32 *priority) {
  s32 delta = 0;

  if (decoded->action != AI_ACTION_DISCARD &&
      decoded->action != AI_ACTION_PERM_CARD_DISCARD)
    return;

  if (ctx->preferredEmptyMonsterCol != 0xFF ||
      ctx->hasBeatableFaceUpTarget)
    delta -= (s32)AI_MOD_DELTA_MIN;

  AiMod_ApplyDelta(priority, delta);
}

void AiApplyModifiers(struct AiDecisionContext *ctx) {
  u16 i;

  for (i = 0; i < ctx->actionCount; i++) {
    struct AiDecodedAction decoded;
    u16 actionIndex = ctx->entries[i].actionIndex;
    u32 *priority = &ctx->entries[i].priority;

    AiDecodeActionIndex(actionIndex, &decoded);

    AiMod_LpMood(ctx, actionIndex, priority);
    AiMod_SetupBias(ctx, actionIndex, priority);
    AiMod_SummonQuality(ctx, &decoded, priority);
    AiMod_SetBackrowPlacement(ctx, &decoded, priority);
    AiMod_DuelMemory(ctx, actionIndex, priority);
    AiMod_AttackTargeting(ctx, &decoded, priority);
    AiMod_AttackOrder(ctx, &decoded, priority);
    AiMod_TributeBoard(ctx, &decoded, priority);
    AiMod_OpponentHandRead(ctx, &decoded, priority);
    AiMod_WastefulLine(ctx, &decoded, priority);
  }
}
