#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fenrir.h"

static u8 GraveyardTopIsWaterMonster(u8 turnDuelist)
{
  u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

  if (cardId == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

u8 CanSpecialSummonFenrirFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != FENRIR)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardTopIsWaterMonster(ACTIVE_DUELIST))
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonFenrirFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonFenrirFromHand(handZone))
    return FALSE;

  GetGraveCardAndClearGrave(ACTIVE_DUELIST);

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
