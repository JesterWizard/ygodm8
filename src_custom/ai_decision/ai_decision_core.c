#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "the_dark_door.h"
#include "gravity_bind.h"
#include "reaper_on_the_nightmare.h"

extern u16 RandRangeU16(u16 min, u16 max);

#define AI_ACTION_FILTER_NONE            0
#define AI_ACTION_FILTER_DESTROY_FACE_UP 1

static u8 AiDecision_ActionSummonsToMonsterCol(u16 actionIndex, u8 monsterCol);
static u8 AiDecision_ActionSetsToBackrowCol(u16 actionIndex, u8 backrowCol);
static u8 AiDecision_ActionPassesPlacementRules(
    u16 actionIndex, const struct AiDecisionContext *ctx);

static u8 AiDecision_IsAttackCategory(u16 actionIndex) {
  struct AiDecodedAction decoded;

  AiDecodeActionIndex(actionIndex, &decoded);
  return decoded.category == AI_CATEGORY_ATTACK ||
         decoded.category == AI_CATEGORY_DIRECT;
}

// ponytail: vanilla face-up attacks finish at AI_PRIORITY_DISABLE; smarter AI must not treat that as "skip".
static void AiDecision_NormalizeVanillaAttackPriorities(struct AiDecisionContext *ctx) {
  u16 i;

  for (i = 0; i < ctx->actionCount; i++) {
    if (ctx->entries[i].priority != AI_PRIORITY_DISABLE)
      continue;
    if (!AiDecision_IsAttackCategory(ctx->entries[i].actionIndex))
      continue;
    if (AiTactics_IsFutileIndestructibleDefenseLine(ctx->entries[i].actionIndex))
      continue;
    ctx->entries[i].priority = AI_PRIORITY_DISABLE - AI_MOD_DELTA_MIN;
  }
}

static void AiDecision_BoostBattleDamageVsIndestructible(struct AiDecisionContext *ctx) {
  u16 i;

  for (i = 0; i < ctx->actionCount; i++) {
    struct AiDecodedAction decoded;
    struct DuelCard *defender;

    if (!AiTactics_ActionDealsFaceUpBattleDamage(ctx->entries[i].actionIndex))
      continue;

    AiDecodeActionIndex(ctx->entries[i].actionIndex, &decoded);
    defender = gTurnZones[decoded.zone1Row][decoded.zone1Col];
    if (!IsBattleIndestructibleMonster(defender->id))
      continue;

    if (ctx->entries[i].priority == 0)
      ctx->entries[i].priority = AI_PRIORITY_DISABLE - AI_MOD_DELTA_MIN;
    else
      ctx->entries[i].priority += AI_MOD_DELTA_MIN;
  }
}

static u8 AiDecision_ActionSummonsToMonsterCol(
    u16 actionIndex, u8 monsterCol) {
  struct AiDecodedAction decoded;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category != AI_CATEGORY_SUMMON)
    return FALSE;
  if (decoded.action == AI_ACTION_ACTIVATE_RITUAL_SPELL)
    return FALSE;
  if (decoded.zone1Row != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;
  if (decoded.zone1Col != monsterCol)
    return FALSE;

  return TRUE;
}

static u8 AiDecision_ActionSetsToBackrowCol(u16 actionIndex, u8 backrowCol) {
  struct AiDecodedAction decoded;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category != AI_CATEGORY_SET_SPELL &&
      decoded.category != AI_CATEGORY_SET_TRAP)
    return FALSE;
  if (decoded.zone1Row != ACTIVE_DUELIST_BACKROW)
    return FALSE;
  if (decoded.zone1Col != backrowCol)
    return FALSE;

  return TRUE;
}

static u8 AiDecision_ActionPassesPlacementRules(
    u16 actionIndex, const struct AiDecisionContext *ctx) {
  struct AiDecodedAction decoded;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category == AI_CATEGORY_SUMMON &&
      decoded.action != AI_ACTION_ACTIVATE_RITUAL_SPELL &&
      decoded.zone1Row == ACTIVE_DUELIST_MONSTER_ROW &&
      ctx->preferredEmptyMonsterCol != 0xFF &&
      decoded.zone1Col != ctx->preferredEmptyMonsterCol)
    return FALSE;

  if ((decoded.category == AI_CATEGORY_SET_SPELL ||
       decoded.category == AI_CATEGORY_SET_TRAP) &&
      decoded.zone1Row == ACTIVE_DUELIST_BACKROW &&
      ctx->preferredEmptyBackrowCol != 0xFF &&
      decoded.zone1Col != ctx->preferredEmptyBackrowCol)
    return FALSE;

  return TRUE;
}

static u8 AiDecision_ActionPassesFilter(
    u16 actionIndex,
    u8 filterKind,
    u8 filterArg,
    const struct AiDecisionContext *ctx,
    u8 enforcePlacement) {
  if (enforcePlacement &&
      !AiDecision_ActionPassesPlacementRules(actionIndex, ctx))
    return FALSE;

  switch (filterKind) {
  case AI_ACTION_FILTER_DESTROY_FACE_UP:
    return AiTactics_ActionDestroysFaceUpMonster(actionIndex);
  default:
    return TRUE;
  }
}

static u16 GetVanillaHighestPriorityAction(
    struct AiActionPriorityEntry *entries, u16 actionCount) {
  u16 i;
  u16 bestAction = 0;
  u32 bestPriority = 0;

  for (i = 0; i < actionCount; i++) {
    if (entries[i].priority > bestPriority) {
      bestPriority = entries[i].priority;
      bestAction = entries[i].actionIndex;
    }
  }

  return bestAction;
}

static u8 AiDecision_HasLethalLine(struct AiActionPriorityEntry *entries, u16 actionCount) {
  u16 i;

  for (i = 0; i < actionCount; i++) {
    if (entries[i].priority >= AI_PRIORITY_LETHAL_MIN)
      return TRUE;
  }

  return FALSE;
}

static u8 AiPriorityIsEligible(u32 priority, u32 threshold, u8 lethalOnly) {
  if (priority == 0 || priority == AI_PRIORITY_DISABLE)
    return FALSE;

  if (lethalOnly)
    return priority >= AI_PRIORITY_LETHAL_MIN;

  return priority >= threshold;
}

static u32 AiDecision_BestPriority(
    struct AiActionPriorityEntry *entries,
    u16 actionCount,
    u8 filterKind,
    u8 filterArg,
    const struct AiDecisionContext *ctx,
    u8 enforcePlacement) {
  u16 i;
  u32 bestPriority = 0;

  for (i = 0; i < actionCount; i++) {
    u32 priority = entries[i].priority;

    if (priority == 0 || priority == AI_PRIORITY_DISABLE)
      continue;

    if (!AiDecision_ActionPassesFilter(
            entries[i].actionIndex,
            filterKind,
            filterArg,
            ctx,
            enforcePlacement))
      continue;

    if (priority > bestPriority)
      bestPriority = priority;
  }

  return bestPriority;
}

static u8 AiDecision_FilterIsCompetitive(
    struct AiActionPriorityEntry *entries,
    u16 actionCount,
    u8 filterKind,
    u8 filterArg) {
  u32 globalBest;
  u32 filteredBest;

  if (filterKind == AI_ACTION_FILTER_NONE)
    return FALSE;

  globalBest = AiDecision_BestPriority(
      entries, actionCount, AI_ACTION_FILTER_NONE, 0xFF, NULL, FALSE);
  filteredBest = AiDecision_BestPriority(
      entries, actionCount, filterKind, filterArg, NULL, FALSE);

  if (filteredBest == 0 || globalBest == 0)
    return FALSE;

  if (filteredBest + AI_SMART_FILTER_MARGIN < globalBest)
    return FALSE;

  return TRUE;
}

static u16 PickFromCandidates(
    struct AiActionPriorityEntry *entries,
    u16 actionCount,
    u32 bestPriority,
    u8 lethalOnly,
    u8 filterKind,
    u8 filterArg,
    const struct AiDecisionContext *ctx) {
  u8 enforcePlacement = lethalOnly ? FALSE : TRUE;
  u16 i;
  u16 candidateCount = 0;
  u16 pickedAction = 0;
  u32 threshold;
  u32 topPriority = 0;

  if (bestPriority == 0)
    return 0;

  if (lethalOnly)
    threshold = AI_PRIORITY_LETHAL_MIN;
  else if (bestPriority > AI_SMART_VARIANCE_MARGIN)
    threshold = bestPriority - AI_SMART_VARIANCE_MARGIN;
  else
    threshold = 0;

  for (i = 0; i < actionCount; i++) {
    u32 priority = entries[i].priority;

    if (!AiPriorityIsEligible(priority, threshold, lethalOnly))
      continue;

    if (!AiDecision_ActionPassesFilter(
            entries[i].actionIndex,
            filterKind,
            filterArg,
            ctx,
            enforcePlacement))
      continue;

    if (priority > topPriority)
      topPriority = priority;
  }

  if (topPriority == 0)
    return 0;

  for (i = 0; i < actionCount; i++) {
    u32 priority = entries[i].priority;

    if (!AiPriorityIsEligible(priority, threshold, lethalOnly))
      continue;

    if (!AiDecision_ActionPassesFilter(
            entries[i].actionIndex,
            filterKind,
            filterArg,
            ctx,
            enforcePlacement))
      continue;

    if (priority != topPriority)
      continue;

    candidateCount++;
    if (candidateCount == 1 || RandRangeU16(0, candidateCount - 1) == 0)
      pickedAction = entries[i].actionIndex;
  }

  return pickedAction;
}

static u8 sAiWasPlayerTurn APPEND_DATA = TRUE;

static void AiDecision_TrackOpponentTurn(void) {
  if (sAiWasPlayerTurn && WhoseTurn() == DUEL_OPPONENT) {
    AiMemory_OnOpponentTurnStart();
    sAiWasPlayerTurn = FALSE;
  }
  if (WhoseTurn() == DUEL_PLAYER)
    sAiWasPlayerTurn = TRUE;
}

static void AiDecision_BuildContext(struct AiDecisionContext *ctx) {
  AiDecision_TrackOpponentTurn();

  ctx->entries = gUnk_8DFF6A4->entries;
  ctx->actionCount = gUnk_8DFF6A4->actionCount;
  ctx->aiLifePoints = gDuelLifePoints[DUEL_OPPONENT];
  ctx->playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  ctx->lifePointDelta = (s16)ctx->aiLifePoints - (s16)ctx->playerLifePoints;
  ctx->opponentTurnCount = gAiDuelMemory.opponentTurnCount;
  ctx->hasLethalLine = AiDecision_HasLethalLine(ctx->entries, ctx->actionCount);
  ctx->playerHasSetBackrow = FALSE;
  ctx->hasBeatableFaceUpTarget = FALSE;
  ctx->weakestAttackerAtk = 0;
  ctx->strongestAttackerAtk = 0;
  ctx->visibleHandThreat = 0;
  ctx->visibleHandHasMonster = FALSE;
  ctx->visibleHandHasTrapOrSpell = FALSE;
  ctx->preferredEmptyMonsterCol = 0xFF;
  ctx->preferredEmptyBackrowCol = 0xFF;

  AiTactics_FillContext(ctx);
}

static u8 AiDecision_ChooseActionFilter(
    struct AiDecisionContext *ctx, u8 *filterArgOut) {
  u8 filterKind;

  *filterArgOut = 0xFF;

  if (ctx->hasLethalLine)
    return AI_ACTION_FILTER_NONE;

  if (AiTactics_ShouldForceDestroyFaceUp(ctx)) {
    filterKind = AI_ACTION_FILTER_DESTROY_FACE_UP;
    if (AiDecision_FilterIsCompetitive(
            ctx->entries, ctx->actionCount, filterKind, 0xFF))
      return filterKind;
  }

  return AI_ACTION_FILTER_NONE;
}

static u8 AiDecision_ShouldDisableAttackAction(const struct AiDecodedAction *decoded)
{
  if (IsAiAttackAction(decoded->action) || IsAiDirectAttackAction(decoded->action))
    return TRUE;

  if (decoded->action == AI_ACTION_ATTACK_POSITION ||
      decoded->action == AI_ACTION_PERM_CARD_ATTACK_POSITION)
    return TRUE;

  return FALSE;
}

static void AiDecision_DisableBlockedAttackActions(struct AiDecisionContext *ctx)
{
  u16 i;
  u8 globalAttackAllowed =
      DebugRuleset_CanAttackThisTurn() && TheDarkDoor_CanAttackThisTurn();

  for (i = 0; i < ctx->actionCount; i++) {
    struct AiDecodedAction decoded;

    AiDecodeActionIndex(ctx->entries[i].actionIndex, &decoded);
    if (!AiDecision_ShouldDisableAttackAction(&decoded))
      continue;

    if (!globalAttackAllowed ||
        !GravityBind_CanMonsterAttack(decoded.primaryCardId))
      ctx->entries[i].priority = 0;
  }
}

u16 AiDecision_PickAction(void) {
  struct AiDecisionContext ctx;
  u32 bestPriority;
  u8 filterKind;
  u8 filterArg;

  AiDecision_BuildContext(&ctx);
  AiDecision_DisableBlockedAttackActions(&ctx);
  AiDecision_BoostBattleDamageVsIndestructible(&ctx);

  if (gRuntimeConfig.enable_smarter_ai != TRUE)
    return GetVanillaHighestPriorityAction(ctx.entries, ctx.actionCount);

  AiDecision_NormalizeVanillaAttackPriorities(&ctx);
  AiApplyModifiers(&ctx);

  filterKind = AiDecision_ChooseActionFilter(&ctx, &filterArg);

  bestPriority = AiDecision_BestPriority(
      ctx.entries, ctx.actionCount, filterKind, filterArg, &ctx, !ctx.hasLethalLine);

  if (ctx.hasLethalLine)
    return PickFromCandidates(
        ctx.entries,
        ctx.actionCount,
        bestPriority,
        TRUE,
        AI_ACTION_FILTER_NONE,
        0xFF,
        &ctx);

  return PickFromCandidates(
      ctx.entries,
      ctx.actionCount,
      bestPriority,
      FALSE,
      filterKind,
      filterArg,
      &ctx);
}

void AiApplyModifiers(struct AiDecisionContext *ctx);
