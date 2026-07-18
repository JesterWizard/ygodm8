#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "ai_sim.h"
#include "ai_spell_targets.h"
#include "duel_helpers.h"
#include "card.h"
#include "configs/runtime.h"
#include "constants/spell_effects.h"
#include "duel.h"

#define AI_ACTION_TABLE_COUNT 0x3B2
/* ponytail: keep ≤ a few legality checks; board scored once. Target << 60 frames. */
#define AI_FAST_CANDIDATE_CAP  6
#define AI_FAST_MAX_LEGAL      3
#define AI_FAST_SCORE_LETHAL   30000
#define AI_FAST_SCORE_DEFEND   11000

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

struct AiFastCandidate {
  u16 index;
  u16 score;
};

/* Bit i set => monster col i should be/stay in defense (face-down set or flip). */
struct AiFastBoardCtx {
  u8 handHasPermCard;
  u8 handHasMonster;
  u8 emptyMonsterZones;
  u8 summoningBlocked;
  u8 defendMask;
  u16 strongestEnemyAtk;
};

extern const struct AI_Command gAED58[];

typedef u8 (*FnU8Void)(void);

static inline u8 CallThumbU8(u32 addr)
{
  return ((FnU8Void)(addr | 1))();
}

static u8 AiSimFastZoneEmpty(u8 row, u8 col)
{
  if (row > ACTIVE_DUELIST_HAND)
    return FALSE;
  return gTurnZones[row][col]->id == CARD_NONE;
}

/* TRUE if our monster loses to a face-up enemy ATKer (ATK and/or attribute). */
static u8 AiSimFastLosesToBoard(u16 ourAtk, u8 ourAttr)
{
  u8 eCol;

  for (eCol = 0; eCol < MAX_ZONES_IN_ROW; eCol++) {
    struct DuelCard *enemy = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][eCol];
    u16 enemyAtk;
    u8 enemyAttr;
    u8 matchup;

    if (enemy->id == CARD_NONE || !enemy->isFaceUp || enemy->isDefending)
      continue;

    SetCardInfo(enemy->id);
    enemyAtk = gCardInfo.atk;
    enemyAttr = gCardInfo.attribute;

    if (gRuntimeConfig.disable_element_system != TRUE) {
      matchup = sub_803FBCC(ourAttr, enemyAttr);
      /* 2 = we are weak to them (e.g. Forest vs Pyro). */
      if (matchup == 2)
        return TRUE;
      /* 0 = we beat their attribute — can stay in ATK even if lower. */
      if (matchup == 0)
        continue;
    }

    if (enemyAtk > ourAtk)
      return TRUE;
  }

  return FALSE;
}

static void AiSimFastScanBoard(struct AiFastBoardCtx *ctx)
{
  u8 col;
  u8 eCol;

  ctx->handHasPermCard = FALSE;
  ctx->handHasMonster = FALSE;
  ctx->emptyMonsterZones = 0;
  ctx->summoningBlocked = gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked;
  ctx->defendMask = 0;
  ctx->strongestEnemyAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_HAND][col];

    if (zone->id == CARD_NONE)
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.unk1E != 0)
      ctx->handHasPermCard = TRUE;
    if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      ctx->handHasMonster = TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id == CARD_NONE)
      ctx->emptyMonsterZones++;
  }

  for (eCol = 0; eCol < MAX_ZONES_IN_ROW; eCol++) {
    struct DuelCard *enemy = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][eCol];

    if (enemy->id == CARD_NONE || !enemy->isFaceUp || enemy->isDefending)
      continue;
    SetCardInfo(enemy->id);
    if (gCardInfo.atk > ctx->strongestEnemyAtk)
      ctx->strongestEnemyAtk = gCardInfo.atk;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *ours = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (ours->id == CARD_NONE)
      continue;

    SetCardInfo(ours->id);
    /* Face-down after summon, face-up ATK, or already-defending: flag if we lose. */
    if (AiSimFastLosesToBoard(gCardInfo.atk, gCardInfo.attribute))
      ctx->defendMask |= (u8)(1 << col);
  }
}

static u8 AiSimFastTributeCount(u16 action)
{
  switch (action) {
  case AI_ACTION_1_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON:
    return 1;
  case AI_ACTION_2_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    return 2;
  case AI_ACTION_3_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
    return 3;
  default:
    return 0;
  }
}

static u8 AiSimFastRejectEmptyTributes(const struct AI_Command *cmd)
{
  u8 needed = AiSimFastTributeCount(cmd->action);
  u8 positions[3];
  u8 i;

  if (needed == 0)
    return FALSE;

  positions[0] = cmd->zone2Position;
  positions[1] = cmd->zone3Position;
  positions[2] = cmd->zone4Position;

  for (i = 0; i < needed; i++) {
    u8 row = positions[i] >> 4;
    u8 col = positions[i] & 0xF;

    if (positions[i] == 0 || AiSimFastZoneEmpty(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 AiSimFastRejectWastefulTribute(const struct AI_Command *cmd)
{
  u8 needed = AiSimFastTributeCount(cmd->action);
  u8 positions[3];
  u8 i;
  u16 summonAtk;
  u16 maxTributeAtk = 0;
  u8 handRow;
  u8 handCol;
  u16 handId;

  if (needed == 0)
    return FALSE;

  handRow = cmd->zone1Position >> 4;
  handCol = cmd->zone1Position & 0xF;
  if (handRow > ACTIVE_DUELIST_HAND || AiSimFastZoneEmpty(handRow, handCol))
    return FALSE;

  handId = gTurnZones[handRow][handCol]->id;
  SetCardInfo(handId);
  if (gCardInfo.monsterEffect != 0 || gCardInfo.unk1E != 0 || gCardInfo.ritualEffect != 0)
    return FALSE;

  summonAtk = gCardInfo.atk;
  positions[0] = cmd->zone2Position;
  positions[1] = cmd->zone3Position;
  positions[2] = cmd->zone4Position;

  for (i = 0; i < needed; i++) {
    u8 row = positions[i] >> 4;
    u8 col = positions[i] & 0xF;
    struct DuelCard *zone;

    if (positions[i] == 0 || AiSimFastZoneEmpty(row, col))
      return FALSE;

    zone = gTurnZones[row][col];
    if (!zone->isFaceUp)
      return FALSE;

    SetCardInfo(zone->id);
    if (gCardInfo.atk > maxTributeAtk)
      maxTributeAtk = gCardInfo.atk;
  }

  return maxTributeAtk > summonAtk;
}

static u8 AiSimFastRejectNoopPosition(const struct AI_Command *cmd)
{
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;
  struct DuelCard *zone;

  if (row > ACTIVE_DUELIST_MONSTER_ROW || AiSimFastZoneEmpty(row, col))
    return FALSE;

  zone = gTurnZones[row][col];

  /* Face-down set already defending must not keep winning every think cycle. */
  if (cmd->action == AI_ACTION_DEFENSE_POSITION ||
      cmd->action == AI_ACTION_PERM_CARD_DEFENSE_POSITION)
    return zone->isDefending != 0;

  if (cmd->action == AI_ACTION_ATTACK_POSITION ||
      cmd->action == AI_ACTION_PERM_CARD_ATTACK_POSITION)
    return zone->isFaceUp && zone->isDefending == 0;

  return FALSE;
}

static u8 AiSimFastQuickReject(u16 i, u8 handHasPermCard)
{
  const struct AI_Command *cmd = &gAED58[i];
  u16 action = cmd->action;
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;

  if (action >= AI_ACTION_PERM_CARD_DISCARD && !handHasPermCard)
    return TRUE;

  if (row <= ACTIVE_DUELIST_HAND && AiSimFastZoneEmpty(row, col)) {
    if (IsAiSummonAction(action) || IsAiSetSpellAction(action) ||
        IsAiSetTrapAction(action) || IsAiActivateSpellAction(action) ||
        action == AI_ACTION_DISCARD || IsAiMonsterEffectAction(action))
      return TRUE;
  }

  if (IsAiActivateSpellAction(action)) {
    u16 cardId = CARD_NONE;

    if (row <= ACTIVE_DUELIST_HAND)
      cardId = gTurnZones[row][col]->id;

    if (cardId != CARD_NONE && Duel_IsCardActivationBlocked(cardId))
      return TRUE;

    if (cardId != CARD_NONE
        && GetTypeGroup(cardId) == TYPE_GROUP_SPELL
        && GetSpellType(cardId) == SPELL_TYPE_NORMAL
        && !AiNormalSpellHasActivationTargets(cardId))
      return TRUE;
  }

  if ((IsAiAttackAction(action) || IsAiDefensePositionAction(action) ||
       action == AI_ACTION_ATTACK_POSITION ||
       action == AI_ACTION_PERM_CARD_ATTACK_POSITION) &&
      row <= ACTIVE_DUELIST_MONSTER_ROW && AiSimFastZoneEmpty(row, col))
    return TRUE;

  if (AiSimFastRejectNoopPosition(cmd))
    return TRUE;

  if (AiSimFastRejectEmptyTributes(cmd))
    return TRUE;

  if (AiSimFastRejectWastefulTribute(cmd))
    return TRUE;

  if (cmd->zone2Position != 0) {
    u8 row2 = cmd->zone2Position >> 4;
    u8 col2 = cmd->zone2Position & 0xF;

    if (row2 <= ACTIVE_DUELIST_HAND && AiSimFastZoneEmpty(row2, col2)) {
      if (IsAiTributeSummonAction(action))
        return TRUE;
      if (IsAiSummonAction(action))
        return FALSE;
      if (IsAiSetTrapAction(action))
        return FALSE;
      if (IsAiSetSpellAction(action) && action != AI_ACTION_PLACE_EQUIP_SPELL)
        return FALSE;
      return TRUE;
    }
  }

  return FALSE;
}

/* TRUE if this attack is a clear loss (no elemental advantage, lower/equal ATK). */
static u8 AiSimFastAttackIsSuicide(const struct AI_Command *cmd)
{
  u8 aRow = cmd->zone1Position >> 4;
  u8 aCol = cmd->zone1Position & 0xF;
  u8 dRow;
  u8 dCol;
  struct DuelCard *att;
  struct DuelCard *def;
  u16 atkAtt;
  u16 atkDef;
  u8 attrAtt;
  u8 attrDef;
  u8 matchup;

  if (!IsAiFaceUpAttackAction(cmd->action))
    return FALSE;
  if (cmd->zone2Position == 0)
    return FALSE;

  dRow = cmd->zone2Position >> 4;
  dCol = cmd->zone2Position & 0xF;
  if (AiSimFastZoneEmpty(aRow, aCol) || AiSimFastZoneEmpty(dRow, dCol))
    return FALSE;

  att = gTurnZones[aRow][aCol];
  def = gTurnZones[dRow][dCol];
  if (!def->isFaceUp || def->isDefending)
    return FALSE;

  SetCardInfo(att->id);
  atkAtt = gCardInfo.atk;
  attrAtt = gCardInfo.attribute;
  SetCardInfo(def->id);
  atkDef = gCardInfo.atk;
  attrDef = gCardInfo.attribute;

  if (gRuntimeConfig.disable_element_system != TRUE) {
    matchup = sub_803FBCC(attrAtt, attrDef);
    if (matchup == 0)
      return FALSE;
  }

  return atkAtt <= atkDef;
}

static u16 AiSimFastAttackScore(const struct AI_Command *cmd)
{
  u8 aRow = cmd->zone1Position >> 4;
  u8 aCol = cmd->zone1Position & 0xF;
  u16 atk;
  u16 action = cmd->action;

  if (AiSimFastZoneEmpty(aRow, aCol))
    return 0;

  if (AiSimFastAttackIsSuicide(cmd))
    return 0;

  SetCardInfo(gTurnZones[aRow][aCol]->id);
  atk = gCardInfo.atk;

  if (IsAiDirectAttackAction(action)) {
    if (atk >= gDuelLifePoints[INACTIVE_DUELIST])
      return AI_FAST_SCORE_LETHAL;
    return 9000 + atk / 10;
  }

  if (IsAiFaceUpAttackAction(action)) {
    u8 dRow = cmd->zone2Position >> 4;
    u8 dCol = cmd->zone2Position & 0xF;
    struct DuelCard *def;
    u16 defStat;

    if (cmd->zone2Position == 0 || AiSimFastZoneEmpty(dRow, dCol))
      return 0;

    def = gTurnZones[dRow][dCol];
    if (!def->isFaceUp)
      return 7000 + atk / 20;

    SetCardInfo(def->id);
    defStat = def->isDefending ? gCardInfo.def : gCardInfo.atk;
    if (atk > defStat)
      return 9500 + (atk - defStat) / 10;
    if (atk == defStat)
      return 4000;
    return 0;
  }

  if (IsAiFaceDownAttackAction(action))
    return 6500 + atk / 20;

  return 8000 + atk / 10;
}

static u16 AiSimFastHeuristicScore(u16 actionIndex, const struct AiFastBoardCtx *ctx)
{
  const struct AI_Command *cmd = &gAED58[actionIndex];
  u16 action = cmd->action;
  u16 score;
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;
  u16 cardId = CARD_NONE;

  if (row <= ACTIVE_DUELIST_HAND && !AiSimFastZoneEmpty(row, col))
    cardId = gTurnZones[row][col]->id;

  if (IsAiAttackAction(action))
    return AiSimFastAttackScore(cmd);

  if (IsAiDefensePositionAction(action) ||
      action == AI_ACTION_PERM_CARD_DEFENSE_POSITION) {
    if (row == ACTIVE_DUELIST_MONSTER_ROW && col < MAX_ZONES_IN_ROW &&
        (ctx->defendMask & (u8)(1 << col)) != 0)
      return AI_FAST_SCORE_DEFEND;
    return 400;
  }

  if (action == AI_ACTION_ATTACK_POSITION ||
      action == AI_ACTION_PERM_CARD_ATTACK_POSITION) {
    /* Don't flip threatened / weak matchups to face-up ATK (vanilla sets face-down). */
    if (row == ACTIVE_DUELIST_MONSTER_ROW && col < MAX_ZONES_IN_ROW &&
        (ctx->defendMask & (u8)(1 << col)) != 0)
      return 0;
    return 500;
  }

  if (IsAiActivateSpellAction(action)) {
    score = 10000;
    if (cardId != CARD_NONE) {
      SetCardInfo(cardId);
      if (gCardInfo.spellEffect == SPELL_EFFECT_RAIGEKI ||
          gCardInfo.spellEffect == SPELL_EFFECT_DARK_HOLE ||
          gCardInfo.spellEffect == SPELL_EFFECT_HEAVY_STORM ||
          gCardInfo.spellEffect == SPELL_EFFECT_HARPIES_FEATHER_DUSTER)
        score = 12000;
    }
  } else if (IsAiHighImpactAction(action) || IsAiTributeSummonAction(action)) {
    score = 6000;
  } else if (IsAiSummonAction(action)) {
    score = 5000;
    if (cardId != CARD_NONE && ctx->strongestEnemyAtk != 0) {
      SetCardInfo(cardId);
      /* Prefer not summoning into ATK if weaker than face-up threats (set/def later). */
      if (gCardInfo.atk < ctx->strongestEnemyAtk)
        score = 3500;
    }
    /* Empty zones + hand monsters: keep summons in top-N vs filler attacks. */
    if (!ctx->summoningBlocked && ctx->emptyMonsterZones != 0 &&
        ctx->handHasMonster)
      score += 4000;
  } else if (IsAiMonsterEffectAction(action)) {
    score = 4000;
  } else if (IsAiSetTrapAction(action)) {
    score = 2000;
  } else if (IsAiSetSpellAction(action)) {
    score = 1500;
  } else {
    score = 100;
  }

  if (cardId != CARD_NONE) {
    SetCardInfo(cardId);
    score += gCardInfo.atk / 10;
  }

  return score;
}

static void AiSimFastInsertCandidate(struct AiFastCandidate *list, u8 *count,
                                     u16 index, u16 score)
{
  u8 i;
  u8 slot;

  if (score == 0)
    return;

  if (*count < AI_FAST_CANDIDATE_CAP) {
    slot = *count;
    (*count)++;
  } else if (score <= list[AI_FAST_CANDIDATE_CAP - 1].score) {
    return;
  } else {
    slot = AI_FAST_CANDIDATE_CAP - 1;
  }

  i = slot;
  while (i > 0 && score > list[i - 1].score) {
    list[i] = list[i - 1];
    i--;
  }
  list[i].index = index;
  list[i].score = score;
}

static u32 AiSimFastScoreToPriority(u16 score)
{
  if (score >= AI_FAST_SCORE_LETHAL)
    return AI_PRIORITY_LETHAL_MIN;
  return 0x70000000u + ((u32)score << 10);
}

static void AiSimFastRecord(u16 actionIndex, u16 score)
{
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;
  u16 slot = table->actionCount;

  if (slot >= AI_MAX_EVALUATED_ACTIONS)
    return;

  table->entries[slot].actionIndex = actionIndex;
  table->entries[slot].priority = AiSimFastScoreToPriority(score);
  table->actionCount++;
}

void AiSimulateAllCandidateActionsFast(void)
{
  u16 i;
  u8 candidateCount = 0;
  u8 recorded = 0;
  struct AiFastBoardCtx ctx;
  struct AiFastCandidate candidates[AI_FAST_CANDIDATE_CAP];
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;

  AiClearCommandData();
  table->actionCount = 0;
  AiSimFastScanBoard(&ctx);

  for (i = 0; i < AI_ACTION_TABLE_COUNT; i++) {
    u16 score;

    if (AiSimFastQuickReject(i, ctx.handHasPermCard))
      continue;
    score = AiSimFastHeuristicScore(i, &ctx);
    AiSimFastInsertCandidate(candidates, &candidateCount, i, score);
  }

  for (i = 0; i < candidateCount && recorded < AI_FAST_MAX_LEGAL; i++) {
    AiInitCommandData(candidates[i].index);
    if (CallThumbU8(0x0801A08C) != 1)
      continue;
    AiSimFastRecord(candidates[i].index, candidates[i].score);
    recorded++;
    /* First legal high-value line is enough to act. */
    if (candidates[i].score >= AI_FAST_SCORE_DEFEND)
      break;
  }

  if (recorded == 0) {
    for (i = 0; i < AI_ACTION_TABLE_COUNT; i++) {
      if (AiSimFastQuickReject(i, ctx.handHasPermCard))
        continue;
      AiInitCommandData(i);
      if (CallThumbU8(0x0801A08C) != 1)
        continue;
      AiSimFastRecord(i, AiSimFastHeuristicScore(i, &ctx));
      break;
    }
  }
}
