#include "global.h"
#include "common-chax.h"
#include "call_of_the_haunted.h"
#include "constants/card_ids.h"
#include "embodiment_of_apophis.h"
#include "configs/runtime.h"
#include "debug_ruleset.h"
#include "fairy_box.h"
#include "cats_ear_tribe.h"
#include "graveyard_effects.h"
#include "hayabusa_knight.h"
#include "mermaid_knight.h"
#include "the_unhappy_maiden.h"
#include "vampire_baby.h"
#include "toll.h"
#include "the_dark_door.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;

void sub_801BC00(void);
void sub_8022080(void);
void CheckGraveyardAndLoserFlags(void);
void HandleAtkAndLifePointsAction(void);
void SetAttackAction(s32, s32);
void UpdateAllDuelGfx(void);
void ResolveTheUnhappyMaidenBattleEffect(void);
void ResolveVampireBabyBattleEffect(void);
void ResolveMefistTheInfernalGeneralDiscardBattleEffect(void);
void ResolveGuardianAngelJoanBattleEffect(void);
void ResolveAirknightParshathDrawBattleEffect(void);
void FinishGraveyardDrawBattleResolve(void);

static struct {
  u8 valid;
  u8 isDirect;
  u8 attackerRow;
  u8 attackerCol;
  u8 defenderRow;
  u8 defenderCol;
} sAttackResume APPEND_DATA = {0};

static u8 sRevivedMonsterTurnCol APPEND_DATA = 0xFF;
static u8 sAttackTollAlreadyPaid APPEND_DATA = FALSE;

void MarkCallOfTheHauntedAttackTollPaid(void)
{
  sAttackTollAlreadyPaid = TRUE;
}

void NoteCallOfTheHauntedRevivedMonster(u8 turnCol)
{
  sRevivedMonsterTurnCol = turnCol;
}

u8 CallOfTheHauntedRedirectsDirectAttack(u8 *defenderFixedCol)
{
  struct DuelCard *zone;

  if (defenderFixedCol == NULL || sRevivedMonsterTurnCol == 0xFF)
    return FALSE;

  zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][sRevivedMonsterTurnCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  *defenderFixedCol = sRevivedMonsterTurnCol;
  return TRUE;
}

void SaveCallOfTheHauntedAttackResume(void)
{
  u8 row2;
  u8 col2;
  u8 row3;
  u8 col3;

  sAttackResume.valid = TRUE;
  sAttackResume.attackerRow = gTrapEffectData.originRow;
  sAttackResume.attackerCol = gTrapEffectData.originCol;

  if (WhoseTurn() == DUEL_PLAYER
      && gTrapEffectData.originRow == gDuelCursor.destY
      && gTrapEffectData.originCol == gDuelCursor.destX
      && gDuelCursor.currentY == INACTIVE_DUELIST_MONSTER_ROW) {
    sAttackResume.isDirect = FALSE;
    sAttackResume.defenderRow = gDuelCursor.currentY;
    sAttackResume.defenderCol = gDuelCursor.currentX;
    return;
  }

  row2 = sAI_Command.zone1Position >> 4;
  col2 = sAI_Command.zone1Position & 0xF;
  row3 = sAI_Command.zone2Position >> 4;
  col3 = sAI_Command.zone2Position & 0xF;

  if (row2 == gTrapEffectData.originRow && col2 == gTrapEffectData.originCol
      && row3 == INACTIVE_DUELIST_MONSTER_ROW
      && col3 < MAX_ZONES_IN_ROW
      && gTurnZones[row3][col3]->id != CARD_NONE) {
    sAttackResume.isDirect = FALSE;
    sAttackResume.defenderRow = row3;
    sAttackResume.defenderCol = col3;
    return;
  }

  sAttackResume.isDirect = TRUE;
}

static u8 FixedColForZone(struct DuelCard *zone, u8 fixedRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[fixedRow][i] == zone)
      return i;
  }

  return 0;
}

static u8 SoleMonsterRedirectsAttack(u8 *defenderTurnCol)
{
  u8 col;
  u8 monsterCount = 0;
  u8 soleMonsterCol = 0xFF;
  struct DuelCard *zone;

  if (defenderTurnCol == NULL)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id == CARD_NONE)
      continue;
    monsterCount++;
    soleMonsterCol = col;
  }

  if (monsterCount != 1)
    return FALSE;

  *defenderTurnCol = soleMonsterCol;
  return TRUE;
}

static u8 ShouldRedirectToRevivedMonster(u8 *defenderTurnCol)
{
  u8 revivedCol = sRevivedMonsterTurnCol;

  if (defenderTurnCol == NULL)
    return FALSE;

  if (revivedCol != 0xFF
      && gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][revivedCol]->id != CARD_NONE) {
    if (sAttackResume.isDirect) {
      *defenderTurnCol = revivedCol;
      return TRUE;
    }
    if (SoleMonsterRedirectsAttack(defenderTurnCol))
      return TRUE;
  }

  return SoleMonsterRedirectsAttack(defenderTurnCol);
}

static u8 TryPayResumeAttackToll(void)
{
  if (sAttackTollAlreadyPaid) {
    sAttackTollAlreadyPaid = FALSE;
    return IsDuelOver() != TRUE;
  }

  return TryPayTollAttackCost();
}

void CallOfTheHauntedShowActivationText(void)
{
  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CALL_OF_THE_HAUNTED;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}

void TryResumeInterruptedAttackAfterCallOfTheHaunted(void)
{
  u8 playerCol;
  u8 opponentCol;
  u8 defenderTurnCol;
  u8 attackerFixedCol;
  struct DuelCard *attacker;
  struct DuelCard *defender;

  if (!sAttackResume.valid)
    return;

  sAttackResume.valid = FALSE;

  if (IsDuelOver() == TRUE)
    return;

  attacker = gTurnZones[sAttackResume.attackerRow][sAttackResume.attackerCol];
  if (attacker->id == CARD_NONE)
    return;

  attacker->isDefending = FALSE;
  attacker->isFaceUp = TRUE;
  attacker->isLocked = TRUE;

  if (!TryPayResumeAttackToll())
    return;

  if (ShouldRedirectToRevivedMonster(&defenderTurnCol)) {
    defender = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][defenderTurnCol];
    defender->isFaceUp = TRUE;

    if (WhoseTurn() == DUEL_PLAYER) {
      playerCol = FixedColForZone(attacker, PLAYER_MONSTER_ROW);
      opponentCol = FixedColForZone(defender, OPPONENT_MONSTER_ROW);
    } else {
      playerCol = FixedColForZone(defender, PLAYER_MONSTER_ROW);
      opponentCol = FixedColForZone(attacker, OPPONENT_MONSTER_ROW);
    }

    SetAttackAction(playerCol, opponentCol);
  } else if (sAttackResume.isDirect) {
    attackerFixedCol = (WhoseTurn() == DUEL_PLAYER)
        ? FixedColForZone(attacker, PLAYER_MONSTER_ROW)
        : FixedColForZone(attacker, OPPONENT_MONSTER_ROW);
    PerformDirectAttackOrRedirectToEmbodimentOfApophis(attackerFixedCol);
  } else {
    defender = gTurnZones[sAttackResume.defenderRow][sAttackResume.defenderCol];
    if (defender->id == CARD_NONE)
      return;

    defender->isFaceUp = TRUE;

    if (WhoseTurn() == DUEL_PLAYER) {
      playerCol = FixedColForZone(attacker, PLAYER_MONSTER_ROW);
      opponentCol = FixedColForZone(defender, OPPONENT_MONSTER_ROW);
    } else {
      playerCol = FixedColForZone(defender, PLAYER_MONSTER_ROW);
      opponentCol = FixedColForZone(attacker, OPPONENT_MONSTER_ROW);
    }

    SetAttackAction(playerCol, opponentCol);
  }

  sRevivedMonsterTurnCol = 0xFF;

  TryApplyFairyBoxToPendingAction();
  TryApplyCatsEarTribeToPendingAction();
  HandleAtkAndLifePointsAction();
  DebugRuleset_MarkAttackUsed();
  TheDarkDoor_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
  TryUnlockHayabusaKnightForSecondAttack(attacker);
  TryUnlockMermaidKnightForSecondAttack(attacker);
  sub_801BC00();
  UpdateAllDuelGfx();
  ResolveTheUnhappyMaidenBattleEffect();
  ResolveVampireBabyBattleEffect();
  ResolveMefistTheInfernalGeneralDiscardBattleEffect();
  ResolveGuardianAngelJoanBattleEffect();
  ResolveAirknightParshathDrawBattleEffect();
  sub_8022080();
  FinishGraveyardDrawBattleResolve();
}
