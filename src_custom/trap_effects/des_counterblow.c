#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "des_counterblow.h"
#include "duel_helpers.h"

struct DesCounterblowActionData {
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
};

extern struct DesCounterblowActionData sActionData;

static void ActivateDES_COUNTERBLOWZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DES_COUNTERBLOW) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateDES_COUNTERBLOWOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DES_COUNTERBLOW, ActivateDES_COUNTERBLOWZone);
}

void TryApplyDesCounterblowAfterDirectDamage(u8 damagedFixedDuelist)
{
  struct DuelCard *attacker;
  u8 attackerRow;
  u8 attackerCol;
  u8 gy;

  if (Duel_FindBackrowCard(damagedFixedDuelist, DES_COUNTERBLOW, TRUE) == NULL)
    return;

  if (damagedFixedDuelist == DUEL_PLAYER) {
    if (sActionData.playerCardId != CARD_NONE)
      return; /* not a direct attack */
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
    gy = DUEL_OPPONENT;
  } else {
    if (sActionData.opponentCardId != CARD_NONE)
      return;
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
    gy = DUEL_PLAYER;
  }

  attacker = gFixedZones[attackerRow][attackerCol];
  if (attacker == NULL || attacker->id == CARD_NONE)
    return;

  Duel_ShowEffectText(DES_COUNTERBLOW);
  Duel_DestroyZone(attacker, gy, TRUE);
}
