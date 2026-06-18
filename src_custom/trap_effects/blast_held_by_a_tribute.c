#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "summon_tribute.h"
#include "blast_held_by_a_tribute.h"

#define BLAST_HELD_BY_A_TRIBUTE_DAMAGE 1000

static u8 *MaskForMonsterRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return &gTributeSummonedMonsterMaskOpponentRow;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return &gTributeSummonedMonsterMaskPlayerRow;
  return NULL;
}

static u8 MaskBitForFixedCol(u8 fixedCol)
{
  if (fixedCol >= MAX_ZONES_IN_ROW)
    return 0;
  return (u8)(1 << fixedCol);
}

void BlastHeldByATribute_ClearAllMarks(void)
{
  gTributeSummonedMonsterMaskOpponentRow = 0;
  gTributeSummonedMonsterMaskPlayerRow = 0;
}

static void SetMarkAtFixedMonsterZone(u8 fixedRow, u8 fixedCol)
{
  u8 *mask = MaskForMonsterRow(fixedRow);
  u8 bit = MaskBitForFixedCol(fixedCol);

  if (mask != NULL && bit != 0)
    *mask |= bit;
}

static void ClearMarkAtFixedMonsterZone(u8 fixedRow, u8 fixedCol)
{
  u8 *mask = MaskForMonsterRow(fixedRow);
  u8 bit = MaskBitForFixedCol(fixedCol);

  if (mask != NULL && bit != 0)
    *mask &= (u8)~bit;
}

static u8 MarkIsSetAtFixedMonsterZone(u8 fixedRow, u8 fixedCol)
{
  u8 *mask = MaskForMonsterRow(fixedRow);

  if (mask == NULL)
    return FALSE;

  return (*mask & MaskBitForFixedCol(fixedCol)) != 0;
}

void BlastHeldByATribute_ClearZoneMark(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  ClearMarkAtFixedMonsterZone(fixedRow, fixedCol);
}

void BlastHeldByATribute_TransferZoneMark(struct DuelCard *dst, struct DuelCard *src)
{
  u8 srcRow;
  u8 srcCol;
  u8 dstRow;
  u8 dstCol;

  if (src == NULL || dst == NULL)
    return;

  if (!Duel_FindFixedMonsterZone(src, &srcRow, &srcCol))
    return;
  if (!Duel_FindFixedMonsterZone(dst, &dstRow, &dstCol))
    return;

  if (!MarkIsSetAtFixedMonsterZone(srcRow, srcCol))
    return;

  ClearMarkAtFixedMonsterZone(srcRow, srcCol);
  SetMarkAtFixedMonsterZone(dstRow, dstCol);
}

void TryBlastHeldByATributeOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (GetPendingSummonTributeCount() == 0)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  SetMarkAtFixedMonsterZone(fixedRow, fixedCol);
}

void BlastHeldByATribute_MarkTributeSummonedMonster(u16 cardId)
{
  u8 col;
  struct DuelCard *zone;

  if (cardId == CARD_NONE || GetPendingSummonTributeCount() == 0)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id != cardId)
      continue;

    {
      u8 fixedRow;
      u8 fixedCol;

      if (Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
        SetMarkAtFixedMonsterZone(fixedRow, fixedCol);
    }
    return;
  }
}

u8 BlastHeldByATribute_WasTributeSummoned(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return FALSE;

  return MarkIsSetAtFixedMonsterZone(fixedRow, fixedCol);
}

u8 BlastHeldByATribute_ShouldActivateTrap(void)
{
  struct DuelCard *attacker;

  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  attacker = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (attacker == NULL || attacker->id != gTrapEffectData.originCardId)
    return FALSE;

  return BlastHeldByATribute_WasTributeSummoned(attacker);
}

static u8 IsFaceUpAttackPositionMonster(struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE && zone->isFaceUp == TRUE
      && zone->isDefending == FALSE && !IsGodCard(zone->id);
}

APPEND_TEXT void EffectBlastHeldByATribute(void)
{
  enum DuelActionResult destroyResult;

  Duel_ShowTrapResponseText(BLAST_HELD_BY_A_TRIBUTE, gTrapEffectData.originCardId);

  if (IsDuelOver() == TRUE)
    return;

  destroyResult = Duel_DestroyAllMonstersMatching(
      ACTIVE_DUELIST_MONSTER_ROW, IsFaceUpAttackPositionMonster, FALSE);

  if (destroyResult == DUEL_ACTION_OK) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -BLAST_HELD_BY_A_TRIBUTE_DAMAGE, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, TRUE);
}
