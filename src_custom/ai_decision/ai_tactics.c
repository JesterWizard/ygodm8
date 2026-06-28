#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "board_placement.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_helpers.h"

static void AiTactics_GetMonsterStats(
    struct DuelCard *card, u16 *atkOut, u16 *defOut, u8 *attrOut) {
  if (card->id == CARD_NONE) {
    *atkOut = 0;
    *defOut = 0;
    *attrOut = ATTRIBUTE_NONE;
    return;
  }

  gStatMod.card = card->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(card);
  SetFinalStat(&gStatMod);
  *atkOut = gCardInfo.atk;
  *defOut = gCardInfo.def;
  *attrOut = gCardInfo.attribute;
}

static u8 AiTactics_AttackerBeatsDefender(
    struct DuelCard *attacker, struct DuelCard *defender) {
  u16 atkAtt;
  u16 defAtt;
  u16 atkDef;
  u16 defDef;
  u8 attrAtt;
  u8 attrDef;
  u8 matchup;

  AiTactics_GetMonsterStats(attacker, &atkAtt, &defAtt, &attrAtt);
  AiTactics_GetMonsterStats(defender, &atkDef, &defDef, &attrDef);

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

static u8 AiTactics_AttackerCanDestroyDefender(
    struct DuelCard *attacker, struct DuelCard *defender) {
  if (!AiTactics_AttackerBeatsDefender(attacker, defender))
    return FALSE;
  return CanMonsterBeDestroyedByBattle(defender->id, INACTIVE_DUELIST, 0, 0);
}

static u8 AiTactics_AttackHasMeaningfulOutcome(
    struct DuelCard *attacker, struct DuelCard *defender) {
  if (!AiTactics_AttackerBeatsDefender(attacker, defender))
    return FALSE;
  if (CanMonsterBeDestroyedByBattle(defender->id, INACTIVE_DUELIST, 0, 0))
    return TRUE;
  /* ponytail: indestructible in DEF survives with no LP change; ATK still chips LP. */
  return !defender->isDefending;
}

static u8 AiTactics_PlayerHasSetBackrow(void) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gTurnZones[INACTIVE_DUELIST_BACKROW][col];

    if (card->id != CARD_NONE && !card->isFaceUp)
      return TRUE;
  }

  return FALSE;
}

static void AiTactics_MeasureAttackers(u16 *weakestAtk, u16 *strongestAtk) {
  u8 col;
  u16 minAtk = 0xFFFF;
  u16 maxAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;
    u16 def;
    u8 attr;

    if (card->id == CARD_NONE || card->isDefending)
      continue;

    AiTactics_GetMonsterStats(card, &atk, &def, &attr);
    if (atk < minAtk)
      minAtk = atk;
    if (atk > maxAtk)
      maxAtk = atk;
  }

  *weakestAtk = minAtk == 0xFFFF ? 0 : minAtk;
  *strongestAtk = maxAtk;
}

static u8 AiTactics_HasBeatableFaceUpTarget(void) {
  u8 aiCol;
  u8 playerCol;

  for (aiCol = 0; aiCol < MAX_ZONES_IN_ROW; aiCol++) {
    struct DuelCard *attacker = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][aiCol];

    if (attacker->id == CARD_NONE || attacker->isDefending)
      continue;

    for (playerCol = 0; playerCol < MAX_ZONES_IN_ROW; playerCol++) {
      struct DuelCard *defender = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][playerCol];

      if (defender->id == CARD_NONE || !defender->isFaceUp)
        continue;

      if (AiTactics_AttackHasMeaningfulOutcome(attacker, defender))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 AiTactics_PreferredEmptyMonsterCol(void) {
  return Board_PreferredEmptyMonsterTurnCol();
}

static u8 AiTactics_PreferredEmptyBackrowCol(void) {
  return Board_PreferredEmptyBackrowTurnCol();
}

static void AiTactics_ScanVisibleHand(
    u8 *threatOut, u8 *hasMonsterOut, u8 *hasTrapOrSpellOut) {
  u8 col;
  u8 threat = 0;
  u8 hasMonster = FALSE;
  u8 hasTrapOrSpell = FALSE;

  *threatOut = 0;
  *hasMonsterOut = FALSE;
  *hasTrapOrSpellOut = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gFixedZones[PLAYER_HAND][col];

    if (card->id == CARD_NONE)
      continue;
    if (!CanOpponentSeeCard(PLAYER_HAND, col))
      continue;

    SetCardInfo(card->id);

    if (gCardInfo.type == TYPE_TRAP || gCardInfo.color == COLOR_TRAP) {
      threat += 24;
      hasTrapOrSpell = TRUE;
    } else if (gCardInfo.type == TYPE_SPELL || gCardInfo.color == COLOR_SPELL) {
      threat += 14;
      hasTrapOrSpell = TRUE;
    } else if (gCardInfo.type < TYPE_SPELL) {
      hasMonster = TRUE;
      if (gCardInfo.atk >= 2000)
        threat += 22;
      else if (gCardInfo.atk >= 1500)
        threat += 12;
      if (gCardInfo.level >= 5)
        threat += 10;
    }
  }

  *threatOut = threat > 100 ? 100 : threat;
  *hasMonsterOut = hasMonster;
  *hasTrapOrSpellOut = hasTrapOrSpell;
}

void AiTactics_FillContext(struct AiDecisionContext *ctx) {
  AiMemory_RefreshBoardKnowledge();

  ctx->playerHasSetBackrow = AiTactics_PlayerHasSetBackrow();
  ctx->hasBeatableFaceUpTarget = AiTactics_HasBeatableFaceUpTarget();
  ctx->preferredEmptyMonsterCol = AiTactics_PreferredEmptyMonsterCol();
  ctx->preferredEmptyBackrowCol = AiTactics_PreferredEmptyBackrowCol();
  AiTactics_MeasureAttackers(&ctx->weakestAttackerAtk, &ctx->strongestAttackerAtk);
  AiTactics_ScanVisibleHand(
      &ctx->visibleHandThreat,
      &ctx->visibleHandHasMonster,
      &ctx->visibleHandHasTrapOrSpell);
}

u8 AiTactics_AttackerBeatsDefenderAt(
    u8 attackerRow, u8 attackerCol, u8 defenderRow, u8 defenderCol) {
  struct DuelCard *attacker;
  struct DuelCard *defender;

  if (attackerRow >= 5 || defenderRow >= 5)
    return FALSE;

  attacker = gTurnZones[attackerRow][attackerCol];
  defender = gTurnZones[defenderRow][defenderCol];

  if (attacker->id == CARD_NONE || defender->id == CARD_NONE)
    return FALSE;

  return AiTactics_AttackerBeatsDefender(attacker, defender);
}

static u8 AiTactics_AttackerCanDestroyDefenderAt(
    u8 attackerRow, u8 attackerCol, u8 defenderRow, u8 defenderCol) {
  struct DuelCard *attacker;
  struct DuelCard *defender;

  if (attackerRow >= 5 || defenderRow >= 5)
    return FALSE;

  attacker = gTurnZones[attackerRow][attackerCol];
  defender = gTurnZones[defenderRow][defenderCol];

  if (attacker->id == CARD_NONE || defender->id == CARD_NONE)
    return FALSE;

  return AiTactics_AttackerCanDestroyDefender(attacker, defender);
}

u8 AiTactics_ActionDestroysFaceUpMonster(u16 actionIndex) {
  struct AiDecodedAction decoded;
  struct DuelCard *defender;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category != AI_CATEGORY_ATTACK)
    return FALSE;
  if (!IsAiFaceUpAttackAction(decoded.action))
    return FALSE;
  if (decoded.zone1Row != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  defender = gTurnZones[decoded.zone1Row][decoded.zone1Col];
  if (defender->id == CARD_NONE || !defender->isFaceUp)
    return FALSE;

  return AiTactics_AttackerCanDestroyDefenderAt(
      decoded.zone0Row,
      decoded.zone0Col,
      decoded.zone1Row,
      decoded.zone1Col);
}

u8 AiTactics_ActionDealsFaceUpBattleDamage(u16 actionIndex) {
  struct AiDecodedAction decoded;
  struct DuelCard *defender;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category != AI_CATEGORY_ATTACK)
    return FALSE;
  if (!IsAiFaceUpAttackAction(decoded.action))
    return FALSE;
  if (decoded.zone1Row != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  defender = gTurnZones[decoded.zone1Row][decoded.zone1Col];
  if (defender->id == CARD_NONE || !defender->isFaceUp)
    return FALSE;
  if (defender->isDefending)
    return FALSE;

  return AiTactics_AttackerBeatsDefenderAt(
      decoded.zone0Row,
      decoded.zone0Col,
      decoded.zone1Row,
      decoded.zone1Col);
}

u8 AiTactics_IsFutileIndestructibleDefenseLine(u16 actionIndex) {
  struct AiDecodedAction decoded;
  struct DuelCard *attacker;
  struct DuelCard *defender;

  AiDecodeActionIndex(actionIndex, &decoded);

  if (decoded.category != AI_CATEGORY_ATTACK)
    return FALSE;
  if (!IsAiFaceUpAttackAction(decoded.action))
    return FALSE;
  if (decoded.zone1Row != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  attacker = gTurnZones[decoded.zone0Row][decoded.zone0Col];
  defender = gTurnZones[decoded.zone1Row][decoded.zone1Col];
  if (attacker->id == CARD_NONE || defender->id == CARD_NONE || !defender->isFaceUp)
    return FALSE;

  return !CanMonsterBeDestroyedByBattle(defender->id, INACTIVE_DUELIST, 0, 0)
      && defender->isDefending
      && AiTactics_AttackerBeatsDefender(attacker, defender);
}

u8 AiTactics_HasValidDestroyFaceUpLine(
    struct AiActionPriorityEntry *entries, u16 actionCount) {
  u16 i;

  for (i = 0; i < actionCount; i++) {
    if (entries[i].priority == 0 || entries[i].priority == AI_PRIORITY_DISABLE)
      continue;
    if (AiTactics_ActionDestroysFaceUpMonster(entries[i].actionIndex))
      return TRUE;
  }

  return FALSE;
}

u8 AiTactics_ShouldForceDestroyFaceUp(const struct AiDecisionContext *ctx) {
  if (!ctx->hasBeatableFaceUpTarget)
    return FALSE;

  if (ctx->playerHasSetBackrow && gAiDuelMemory.turnAttackCount == 0)
    return FALSE;

  return AiTactics_HasValidDestroyFaceUpLine(ctx->entries, ctx->actionCount);
}
