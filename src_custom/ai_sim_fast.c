#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "ai_sim.h"
#include "ai_spell_targets.h"
#include "board_placement.h"
#include "duel_attack_restrictions.h"
#include "duel_helpers.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"

#define AI_ACTION_TABLE_COUNT 0x3B2
/* ponytail: hard cap on save/execute sims; attacks use light score instead. */
#define AI_FAST_FULL_SIM_BUDGET 16

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

/* Board flags for one think — only used when fast_ai is on. EWRAM (gc-safe). */
struct AiSimBoardCtx {
  u8 handHasPermCard;
  u8 handHasRitual;
  u8 playerHasSetBackrow;
  u8 hasFaceUpEnemy;
  u8 hasFaceDownEnemy;
  u8 ourMonsterCount;
  u8 summoningBlocked;
  u8 foundLethal;
};

extern const struct AI_Command gAED58[];
extern struct AiSimBoardCtx gAiSimBoard;
extern struct AiActionPriorityTable *gUnk_8DFF6A4;

unsigned char sub_803FBCC(unsigned char a, unsigned char b);

static void AiSimMonsterStats(struct DuelCard *card, u16 *atkOut, u16 *defOut, u8 *attrOut)
{
  gStatMod.card = card->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(card);
  SetFinalStat(&gStatMod);
  *atkOut = gCardInfo.atk;
  *defOut = gCardInfo.def;
  *attrOut = gCardInfo.attribute;
}

void AiSimRecordPriority(u16 actionIndex, u32 priority)
{
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;
  u16 slot = table->actionCount;

  if (slot >= AI_MAX_EVALUATED_ACTIONS)
    return;
  if (priority == 0 || priority == AI_PRIORITY_DISABLE)
    return;

  table->entries[slot].actionIndex = actionIndex;
  table->entries[slot].priority = priority;
  table->actionCount++;
}

/* Mirror vanilla face-up after-priority (sub_8010B08) without executing battle. */
static u32 AiSimLightFaceUpAttackPriority(const struct AI_Command *cmd)
{
  u8 aRow = cmd->zone1Position >> 4;
  u8 aCol = cmd->zone1Position & 0xF;
  u8 dRow = cmd->zone2Position >> 4;
  u8 dCol = cmd->zone2Position & 0xF;
  struct DuelCard *att;
  struct DuelCard *def;
  u16 atkAtt;
  u16 defAtt;
  u16 atkDef;
  u16 defDef;
  u8 attrAtt;
  u8 attrDef;
  u16 defStat;
  u8 matchup;
  u32 before;

  att = gTurnZones[aRow][aCol];
  def = gTurnZones[dRow][dCol];
  AiSimMonsterStats(att, &atkAtt, &defAtt, &attrAtt);
  AiSimMonsterStats(def, &atkDef, &defDef, &attrDef);
  before = (u32)atkDef + (u32)defDef;
  defStat = def->isDefending ? defDef : atkDef;

  if (gRuntimeConfig.disable_element_system != TRUE) {
    matchup = sub_803FBCC(attrAtt, attrDef);
    if (matchup == 0)
      return before - atkAtt + 0x7EF0A113u;
    if (matchup == 2)
      return AI_PRIORITY_DISABLE;
  }

  if (atkAtt > defStat)
    return before - atkAtt + 0x7EF0A113u;
  if (atkAtt == defStat)
    return before - atkAtt + 0x7EF0A113u;
  return AI_PRIORITY_DISABLE;
}

static u32 AiSimLightDirectAttackPriority(const struct AI_Command *cmd)
{
  u8 aRow = cmd->zone1Position >> 4;
  u8 aCol = cmd->zone1Position & 0xF;
  u16 atk;
  u16 junkDef;
  u8 junkAttr;

  AiSimMonsterStats(gTurnZones[aRow][aCol], &atk, &junkDef, &junkAttr);
  if (atk >= gDuelLifePoints[INACTIVE_DUELIST])
    return 0x7FFFFFFFu;
  if (atk == 0)
    return AI_PRIORITY_DISABLE;
  return (u32)atk + 0x7EEB5B4Au;
}

/* Face-down: keep probing but skip save/exec — modest vanilla-ish band. */
static u32 AiSimLightFaceDownAttackPriority(const struct AI_Command *cmd)
{
  u8 aRow = cmd->zone1Position >> 4;
  u8 aCol = cmd->zone1Position & 0xF;
  u16 atk;
  u16 junkDef;
  u8 junkAttr;

  AiSimMonsterStats(gTurnZones[aRow][aCol], &atk, &junkDef, &junkAttr);
  if (atk == 0)
    return AI_PRIORITY_DISABLE;
  return (u32)atk + 0x7EEB5B3Fu;
}

u8 AiSimTryRecordLightAttack(u16 actionIndex)
{
  const struct AI_Command *cmd = &gAED58[actionIndex];
  u32 prio;

  if (!IsAiAttackAction(cmd->action))
    return FALSE;

  /* ponytail: always light-score; set-backrow full-sim burned the non-attack budget.
   * Ceiling: miss trap-on-attack priority nuance; upgrade = light NO_TRAP + one WITH_TRAP probe. */
  if (IsAiDirectAttackAction(cmd->action))
    prio = AiSimLightDirectAttackPriority(cmd);
  else if (IsAiFaceUpAttackAction(cmd->action))
    prio = AiSimLightFaceUpAttackPriority(cmd);
  else if (IsAiFaceDownAttackAction(cmd->action))
    prio = AiSimLightFaceDownAttackPriority(cmd);
  else
    return FALSE;

  AiSimRecordPriority(actionIndex, prio);
  if (prio >= AI_PRIORITY_LETHAL_MIN)
    AiSimMarkLethalFound();
  return TRUE;
}

u8 AiSimFoundLethal(void)
{
  return gAiSimBoard.foundLethal;
}

u8 AiSimFullSimBudget(void)
{
  return AI_FAST_FULL_SIM_BUDGET;
}

static u8 AiSimZoneEmpty(u8 row, u8 col)
{
  if (row > ACTIVE_DUELIST_HAND)
    return FALSE;
  return gTurnZones[row][col]->id == CARD_NONE;
}

static u8 AiSimIsWithTrapAction(u16 action)
{
  switch (action) {
  case AI_ACTION_DIRECT_ATTACK_WITH_TRAP:
  case AI_ACTION_ATTACK_FACE_UP_WITH_TRAP:
  case AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP:
  case AI_ACTION_ACTIVATE_EQUIP_SPELL_WITH_TRAP:
  case AI_ACTION_ACTIVATE_NORMAL_SPELL_WITH_TRAP:
  case AI_ACTION_PERM_CARD_DIRECT_ATTACK_WITH_TRAP:
  case AI_ACTION_PERM_CARD_ATTACK_FACE_UP_WITH_TRAP:
  case AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_WITH_TRAP:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 AiSimTributeCount(u16 action)
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

static u8 AiSimRejectEmptyTributes(const struct AI_Command *cmd)
{
  u8 needed = AiSimTributeCount(cmd->action);
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

    if (positions[i] == 0 || AiSimZoneEmpty(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 AiSimRejectNoopPosition(const struct AI_Command *cmd)
{
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;
  struct DuelCard *zone;

  if (row > ACTIVE_DUELIST_MONSTER_ROW || AiSimZoneEmpty(row, col))
    return FALSE;

  zone = gTurnZones[row][col];

  if (cmd->action == AI_ACTION_DEFENSE_POSITION ||
      cmd->action == AI_ACTION_PERM_CARD_DEFENSE_POSITION)
    return zone->isDefending != 0;

  if (cmd->action == AI_ACTION_ATTACK_POSITION ||
      cmd->action == AI_ACTION_PERM_CARD_ATTACK_POSITION)
    return zone->isFaceUp && zone->isDefending == 0;

  return FALSE;
}

/* Face-up/down mismatch or attacker that cannot declare — skip before save/exec. */
static u8 AiSimRejectIllegalAttack(const struct AI_Command *cmd)
{
  u8 aRow;
  u8 aCol;
  u8 dRow;
  u8 dCol;
  struct DuelCard *att;
  struct DuelCard *def;

  if (!IsAiAttackAction(cmd->action))
    return FALSE;

  aRow = cmd->zone1Position >> 4;
  aCol = cmd->zone1Position & 0xF;
  if (aRow > ACTIVE_DUELIST_MONSTER_ROW || AiSimZoneEmpty(aRow, aCol))
    return TRUE;

  att = gTurnZones[aRow][aCol];
  if (!Duel_CanMonsterDeclareAttack(att))
    return TRUE;

  if (IsAiDirectAttackAction(cmd->action))
    return FALSE;

  if (cmd->zone2Position == 0)
    return TRUE;

  dRow = cmd->zone2Position >> 4;
  dCol = cmd->zone2Position & 0xF;
  if (AiSimZoneEmpty(dRow, dCol))
    return TRUE;

  def = gTurnZones[dRow][dCol];
  if (IsAiFaceUpAttackAction(cmd->action) && !def->isFaceUp)
    return TRUE;
  if (IsAiFaceDownAttackAction(cmd->action) && def->isFaceUp)
    return TRUE;

  return FALSE;
}

u8 AiSimHandHasPermanentCard(void)
{
  return gAiSimBoard.handHasPermCard;
}

void AiSimScanBoard(void)
{
  u8 col;

  gAiSimBoard.handHasPermCard = FALSE;
  gAiSimBoard.handHasRitual = FALSE;
  gAiSimBoard.playerHasSetBackrow = FALSE;
  gAiSimBoard.hasFaceUpEnemy = FALSE;
  gAiSimBoard.hasFaceDownEnemy = FALSE;
  gAiSimBoard.ourMonsterCount = 0;
  gAiSimBoard.summoningBlocked =
      gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked;
  gAiSimBoard.foundLethal = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_HAND][col];

    if (zone->id == CARD_NONE)
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.unk1E != 0)
      gAiSimBoard.handHasPermCard = TRUE;
    if (GetTypeGroup(zone->id) == TYPE_GROUP_RITUAL || gCardInfo.ritualEffect != 0)
      gAiSimBoard.handHasRitual = TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) == TYPE_GROUP_RITUAL) {
      gAiSimBoard.handHasRitual = TRUE;
      continue;
    }
    SetCardInfo(zone->id);
    if (gCardInfo.ritualEffect != 0)
      gAiSimBoard.handHasRitual = TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id != CARD_NONE)
      gAiSimBoard.ourMonsterCount++;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *enemy = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (enemy->id == CARD_NONE)
      continue;
    if (enemy->isFaceUp)
      gAiSimBoard.hasFaceUpEnemy = TRUE;
    else
      gAiSimBoard.hasFaceDownEnemy = TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gTurnZones[INACTIVE_DUELIST_BACKROW][col];

    if (card->id != CARD_NONE && !card->isFaceUp)
      gAiSimBoard.playerHasSetBackrow = TRUE;
  }
}

void AiSimMarkLethalFound(void)
{
  gAiSimBoard.foundLethal = TRUE;
}

/* Skip candidates that cannot beat a known lethal line. */
u8 AiSimRejectAfterLethal(u16 action)
{
  if (!gAiSimBoard.foundLethal)
    return FALSE;
  if (IsAiAttackAction(action) || IsAiDirectAttackAction(action))
    return FALSE;
  if (IsAiActivateSpellAction(action) || IsAiHighImpactAction(action))
    return FALSE;
  return TRUE;
}

/* Skip candidates that cannot be legal — never invents scores (vanilla sim does). */
u8 AiSimQuickReject(u16 i)
{
  const struct AI_Command *cmd = &gAED58[i];
  u16 action = cmd->action;
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;
  u8 tributes;

  if (AiSimRejectAfterLethal(action))
    return TRUE;

  if (action >= AI_ACTION_PERM_CARD_DISCARD && !gAiSimBoard.handHasPermCard)
    return TRUE;

  /* Trap-check duplicates are redundant with empty opponent backrow. */
  if (!gAiSimBoard.playerHasSetBackrow && AiSimIsWithTrapAction(action))
    return TRUE;

  if (gAiSimBoard.summoningBlocked && IsAiSummonAction(action))
    return TRUE;

  if (!gAiSimBoard.handHasRitual &&
      (action == AI_ACTION_ACTIVATE_RITUAL_SPELL ||
       action == AI_ACTION_PLACE_RITUAL_SPELL))
    return TRUE;

  tributes = AiSimTributeCount(action);
  if (tributes != 0 && tributes > gAiSimBoard.ourMonsterCount)
    return TRUE;

  if (IsAiFaceUpAttackAction(action) && !gAiSimBoard.hasFaceUpEnemy)
    return TRUE;
  if (IsAiFaceDownAttackAction(action) && !gAiSimBoard.hasFaceDownEnemy)
    return TRUE;

  if (row <= ACTIVE_DUELIST_HAND && AiSimZoneEmpty(row, col)) {
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
      row <= ACTIVE_DUELIST_MONSTER_ROW && AiSimZoneEmpty(row, col))
    return TRUE;

  if (AiSimRejectNoopPosition(cmd))
    return TRUE;

  if (AiSimRejectEmptyTributes(cmd))
    return TRUE;

  if (AiSimRejectIllegalAttack(cmd))
    return TRUE;

  /* One destination zone per think — cuts 5× summon/set templates. */
  if (cmd->zone2Position != 0) {
    u8 row2 = cmd->zone2Position >> 4;
    u8 col2 = cmd->zone2Position & 0xF;

    if ((action == AI_ACTION_0_TRIBUTE_SUMMON ||
         action == AI_ACTION_PERM_CARD_0_TRIBUTE_SUMMON) &&
        row2 == ACTIVE_DUELIST_MONSTER_ROW) {
      u8 pref = Board_PreferredEmptyMonsterTurnCol();

      if (pref != 0xFF && col2 != pref)
        return TRUE;
    }
    if ((IsAiSetSpellAction(action) || IsAiSetTrapAction(action)) &&
        row2 == ACTIVE_DUELIST_BACKROW) {
      u8 pref = Board_PreferredEmptyBackrowTurnCol();

      if (pref != 0xFF && col2 != pref)
        return TRUE;
    }
  }

  if (cmd->zone2Position != 0) {
    u8 row2 = cmd->zone2Position >> 4;
    u8 col2 = cmd->zone2Position & 0xF;

    if (row2 <= ACTIVE_DUELIST_HAND && AiSimZoneEmpty(row2, col2)) {
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
