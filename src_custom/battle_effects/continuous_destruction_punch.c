#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "continuous_destruction_punch.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

struct ContinuousDestructionPunchActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct ContinuousDestructionPunchActionData sActionData;

void ClearContinuousDestructionPunchPending(void)
{
  gPendingContinuousDestructionPunchAttackerRow = CONTINUOUS_DESTRUCTION_PUNCH_PENDING_NONE;
  gPendingContinuousDestructionPunchAttackerCol = 0;
}

static u8 MarkPendingAttackerDestroy(u8 attackerRow, u8 attackerCol, u16 attackerCardId)
{
  struct DuelCard *zone;

  if (attackerCardId == CARD_NONE || attackerRow >= 5 || attackerCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[attackerRow][attackerCol];
  if (zone == NULL || zone->id != attackerCardId)
    return FALSE;

  gPendingContinuousDestructionPunchAttackerRow = attackerRow;
  gPendingContinuousDestructionPunchAttackerCol = attackerCol;
  return TRUE;
}

static u8 DefenderControllerHasPunch(u8 defenderDuelist)
{
  return Duel_FindBackrowCard(defenderDuelist, CONTINUOUS_DESTRUCTION_PUNCH, TRUE) != NULL;
}

static u8 TryMarkPunchDestroyAttacker(void)
{
  u8 attackerRow;
  u8 attackerCol;
  u16 attackerCardId;
  u16 attackerAtk;
  u16 defenderDef;
  u8 defenderRow;
  u8 defenderCol;
  u8 defenderDuelist;
  struct DuelCard *defenderZone;

  /* id 2 = player attacks into DEF; id 5 = opponent attacks into DEF. */
  if (sActionData.id != 2 && sActionData.id != 5)
    return FALSE;

  if (sActionData.id == 2) {
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
    attackerCardId = sActionData.playerCardId;
    defenderRow = sActionData.opponentMonsterRow;
    defenderCol = sActionData.unk16;
    defenderDuelist = DUEL_OPPONENT;
  } else {
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
    attackerCardId = sActionData.opponentCardId;
    defenderRow = sActionData.playerMonsterRow;
    defenderCol = sActionData.unkA;
    defenderDuelist = DUEL_PLAYER;
  }

  if (!DefenderControllerHasPunch(defenderDuelist))
    return FALSE;

  defenderZone = gFixedZones[defenderRow][defenderCol];
  if (defenderZone == NULL || defenderZone->id == CARD_NONE || !defenderZone->isDefending)
    return FALSE;

  if (defenderDef <= attackerAtk)
    return FALSE;

  return MarkPendingAttackerDestroy(attackerRow, attackerCol, attackerCardId);
}

void ResolveContinuousDestructionPunchBattleEffect(void)
{
  u8 attackerRow;
  u8 attackerCol;
  struct DuelCard *zone;
  u8 graveyardDuelist;

  attackerRow = gPendingContinuousDestructionPunchAttackerRow;
  if (attackerRow == CONTINUOUS_DESTRUCTION_PUNCH_PENDING_NONE)
    return;

  attackerCol = gPendingContinuousDestructionPunchAttackerCol;
  ClearContinuousDestructionPunchPending();

  zone = gFixedZones[attackerRow][attackerCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  graveyardDuelist = GetDuelistForZone(zone);
  if (graveyardDuelist == 0xFF)
    return;

  Duel_ShowEffectTextTyped(CONTINUOUS_DESTRUCTION_PUNCH, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (zone->id != CARD_NONE)
    Duel_DestroyZone(zone, graveyardDuelist, TRUE);
}

void ApplyContinuousDestructionPunchBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkPunchDestroyAttacker()) {
    ClearContinuousDestructionPunchPending();
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveContinuousDestructionPunchBattleEffect();
}
