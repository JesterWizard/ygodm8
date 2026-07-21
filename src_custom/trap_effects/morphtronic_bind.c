#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "morphtronic_bind.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static void ActivateMORPHTRONIC_BINDZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, MORPHTRONIC_BIND) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateMORPHTRONIC_BINDOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(MORPHTRONIC_BIND, ActivateMORPHTRONIC_BINDZone);
}

static u8 ControlsMorphtronic(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id != CARD_NONE
        && Duel_CardNameContains(zone->id, sMorphtronicName))
      return TRUE;
  }
  return FALSE;
}

u8 MorphtronicBind_BlocksAttack(const struct DuelCard *attacker)
{
  u8 attackerFixed;
  u8 bindController;
  u8 fixedRow;
  u8 col;

  if (attacker == NULL || attacker->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)attacker, &fixedRow, &col))
    return FALSE;

  attackerFixed = Duel_FixedDuelistForMonsterRow(fixedRow);
  bindController = attackerFixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (Duel_FindBackrowCard(bindController, MORPHTRONIC_BIND, TRUE) == NULL)
    return FALSE;
  if (!ControlsMorphtronic(bindController))
    return FALSE;

  SetCardInfo(attacker->id);
  return gCardInfo.level >= 4;
}
