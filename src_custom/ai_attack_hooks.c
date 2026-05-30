#include "global.h"
#include "common-chax.h"
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

LYN_REPLACE_CHECK(sub_800E58C);
void sub_800E58C__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  gTurnZones[row2][col2]->isDefending = FALSE;
  gTurnZones[row2][col2]->isFaceUp = TRUE;
  gTurnZones[row2][col2]->isLocked = TRUE;
  SetAttackActionDirectAttack(4 - col2);
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  CheckGraveyardAndLoserFlags();
}

LYN_REPLACE_CHECK(sub_800E5E4);
void sub_800E5E4__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  gTurnZones[row2][col2]->isDefending = FALSE;
  gTurnZones[row2][col2]->isFaceUp = TRUE;
  gTurnZones[row2][col2]->isLocked = TRUE;
  SetAttackActionDirectAttack(4 - col2);
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  CheckGraveyardAndLoserFlags();
}

LYN_REPLACE_CHECK(sub_800E63C);
void sub_800E63C__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  gTurnZones[row2][col2]->isDefending = FALSE;
  gTurnZones[row2][col2]->isFaceUp = TRUE;
  gTurnZones[row2][col2]->isLocked = TRUE;
  gTurnZones[row3][col3]->isFaceUp = TRUE;
  SetAttackAction(col3, 4 - col2);
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  CheckGraveyardAndLoserFlags();
}

LYN_REPLACE_CHECK(sub_800E6B8);
void sub_800E6B8__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  gTurnZones[row2][col2]->isDefending = FALSE;
  gTurnZones[row2][col2]->isFaceUp = TRUE;
  gTurnZones[row2][col2]->isLocked = TRUE;
  gTurnZones[row3][col3]->isFaceUp = TRUE;
  SetAttackAction(col3, 4 - col2);
  TryApplyFairyBoxToPendingAction();
  HandleAtkAndLifePointsAction();
  CheckGraveyardAndLoserFlags();
}
