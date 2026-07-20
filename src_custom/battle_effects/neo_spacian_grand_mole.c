#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "neo_spacian_grand_mole.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct NeoSpacianGrandMoleActionData {
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

extern struct NeoSpacianGrandMoleActionData sActionData;

void ClearNeoSpacianGrandMolePending(void)
{
  gPendingNeoSpacianGrandMoleRow0 = NEO_SPACIAN_GRAND_MOLE_PENDING_NONE;
  gPendingNeoSpacianGrandMoleCol0 = 0;
  gPendingNeoSpacianGrandMoleRow1 = NEO_SPACIAN_GRAND_MOLE_PENDING_NONE;
  gPendingNeoSpacianGrandMoleCol1 = 0;
}

static u8 CanReturnZoneMonsterToOwnerHand(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return FALSE;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return NumEmptyZonesInRow(gTurnHands[turnDuelist]) > 0;
  }

  return FALSE;
}

static u8 MarkPendingReturn(u8 slot, u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (!CanReturnZoneMonsterToOwnerHand(zone))
    return FALSE;

  if (slot == 0) {
    gPendingNeoSpacianGrandMoleRow0 = targetRow;
    gPendingNeoSpacianGrandMoleCol0 = targetCol;
  } else {
    gPendingNeoSpacianGrandMoleRow1 = targetRow;
    gPendingNeoSpacianGrandMoleCol1 = targetCol;
  }

  return TRUE;
}

static u8 TryMarkGrandMoleBounce(u8 moleRow, u8 moleCol, u8 otherRow, u8 otherCol)
{
  u8 marked = 0;

  if (MarkPendingReturn(0, otherRow, otherCol))
    marked++;
  if (MarkPendingReturn(1, moleRow, moleCol))
    marked++;

  return marked == 2;
}

static u8 ReturnPendingZone(u8 row, u8 col)
{
  struct DuelCard *zone;

  if (row == NEO_SPACIAN_GRAND_MOLE_PENDING_NONE)
    return TRUE;

  zone = gFixedZones[row][col];
  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  return Duel_ReturnMonsterZoneToOwnerHand(zone, TRUE) == DUEL_ACTION_OK;
}

void ResolveNeoSpacianGrandMoleBattleEffect(void)
{
  u8 row0;
  u8 col0;
  u8 row1;
  u8 col1;

  row0 = gPendingNeoSpacianGrandMoleRow0;
  if (row0 == NEO_SPACIAN_GRAND_MOLE_PENDING_NONE)
    return;

  col0 = gPendingNeoSpacianGrandMoleCol0;
  row1 = gPendingNeoSpacianGrandMoleRow1;
  col1 = gPendingNeoSpacianGrandMoleCol1;
  ClearNeoSpacianGrandMolePending();

  Duel_ShowEffectText(NEO_SPACIAN_GRAND_MOLE);
  ReturnPendingZone(row0, col0);
  ReturnPendingZone(row1, col1);
}

void ApplyNeoSpacianGrandMoleBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  ClearNeoSpacianGrandMolePending();

  if (sActionData.playerCardId == NEO_SPACIAN_GRAND_MOLE) {
    if (sActionData.flags & (FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT))
      return;

    if (!TryMarkGrandMoleBounce(
            sActionData.playerMonsterRow, sActionData.unkA,
            sActionData.opponentMonsterRow, sActionData.unk16))
      return;
  } else if (sActionData.opponentCardId == NEO_SPACIAN_GRAND_MOLE) {
    if (sActionData.flags & (FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT))
      return;

    if (!TryMarkGrandMoleBounce(
            sActionData.opponentMonsterRow, sActionData.unk16,
            sActionData.playerMonsterRow, sActionData.unkA))
      return;
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveNeoSpacianGrandMoleBattleEffect();
}
