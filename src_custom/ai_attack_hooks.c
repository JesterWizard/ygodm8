#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "fairy_box.h"

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

void sub_800E58C(void);
void sub_800E5E4(void);
void sub_800E63C(void);
void sub_800E6B8(void);
void SetAttackAction(s32, s32);
void SetAttackActionDirectAttack(int);
void HandleAtkAndLifePointsAction(void);
void CheckGraveyardAndLoserFlags(void);

static u8 AiFixedColForZone(struct DuelCard *zone, u8 fixedRow) {
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[fixedRow][i] == zone)
      return i;
  }

  return 0;
}

static void AiPrepareAttacker(struct DuelCard *zone) {
  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  zone->isLocked = TRUE;
}

static void AiAttackDirect(struct DuelCard *attacker) {
  u8 fixedRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  if (!DebugRuleset_AllowDirectAttacks())
    return;

  if (!DebugRuleset_CanAttackThisTurn())
    return;

  if (attacker->id == CARD_NONE)
    return;

  AiPrepareAttacker(attacker);
  SetAttackActionDirectAttack(AiFixedColForZone(attacker, fixedRow));
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  DebugRuleset_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
}

static void AiAttackMonster(struct DuelCard *attacker, struct DuelCard *defender) {
  u8 playerCol;
  u8 opponentCol;

  if (!DebugRuleset_CanAttackThisTurn())
    return;

  if (attacker->id == CARD_NONE)
    return;

  AiPrepareAttacker(attacker);
  defender->isFaceUp = TRUE;

  if (WhoseTurn() == DUEL_PLAYER) {
    playerCol = AiFixedColForZone(attacker, PLAYER_MONSTER_ROW);
    opponentCol = AiFixedColForZone(defender, OPPONENT_MONSTER_ROW);
  } else {
    playerCol = AiFixedColForZone(defender, PLAYER_MONSTER_ROW);
    opponentCol = AiFixedColForZone(attacker, OPPONENT_MONSTER_ROW);
  }

  SetAttackAction(playerCol, opponentCol);
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  DebugRuleset_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
}

LYN_REPLACE_CHECK(sub_800E58C);
void sub_800E58C__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiAttackDirect(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E5E4);
void sub_800E5E4__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiAttackDirect(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E63C);
void sub_800E63C__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  AiAttackMonster(gTurnZones[row2][col2], gTurnZones[row3][col3]);
}

LYN_REPLACE_CHECK(sub_800E6B8);
void sub_800E6B8__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  AiAttackMonster(gTurnZones[row2][col2], gTurnZones[row3][col3]);
}
