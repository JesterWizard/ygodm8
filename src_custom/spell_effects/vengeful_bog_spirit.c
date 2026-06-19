#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "spell_effects.h"
#include "vengeful_bog_spirit.h"

static u8 *MaskForMonsterRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return &gVengefulBogSpiritSummonedMaskOpponentRow;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return &gVengefulBogSpiritSummonedMaskPlayerRow;
  return NULL;
}

static u8 MaskBitForFixedCol(u8 fixedCol)
{
  if (fixedCol >= MAX_ZONES_IN_ROW)
    return 0;
  return (u8)(1 << fixedCol);
}

void VengefulBogSpirit_ClearAllMarks(void)
{
  gVengefulBogSpiritSummonedMaskOpponentRow = 0;
  gVengefulBogSpiritSummonedMaskPlayerRow = 0;
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

u8 IsActivatedVengefulBogSpiritZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == VENGEFUL_BOG_SPIRIT && zone->isFaceUp == TRUE;
}

u8 IsVengefulBogSpiritActiveOnField(void)
{
  if (IsImperialOrderNegatingSpell(VENGEFUL_BOG_SPIRIT))
    return FALSE;

  return Duel_IsBackrowCardOnField(VENGEFUL_BOG_SPIRIT, TRUE);
}

static u8 ZoneWasSummonedThisTurn(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return FALSE;

  return MarkIsSetAtFixedMonsterZone(fixedRow, fixedCol);
}

u8 VengefulBogSpirit_CanMonsterAttack(const struct DuelCard *zone)
{
  if (!IsVengefulBogSpiritActiveOnField())
    return TRUE;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  return !ZoneWasSummonedThisTurn((struct DuelCard *)zone);
}

void VengefulBogSpirit_ClearZoneMark(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  ClearMarkAtFixedMonsterZone(fixedRow, fixedCol);
}

void VengefulBogSpirit_TransferZoneMark(struct DuelCard *dst, struct DuelCard *src)
{
  u8 srcRow;
  u8 srcCol;
  u8 dstRow;
  u8 dstCol;

  if (dst == NULL || src == NULL)
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

static void MarkZoneIfActive(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (!IsVengefulBogSpiritActiveOnField())
    return;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  SetMarkAtFixedMonsterZone(fixedRow, fixedCol);
}

void TryVengefulBogSpiritOnMonsterPlacement(struct DuelCard *zone)
{
  MarkZoneIfActive(zone);
}

void TryVengefulBogSpiritOnFlipSummon(struct DuelCard *zone)
{
  MarkZoneIfActive(zone);
}

APPEND_TEXT void EffectVengefulBogSpirit(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(VENGEFUL_BOG_SPIRIT);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void VengefulBogSpirit_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = VENGEFUL_BOG_SPIRIT;
  zone.isFaceUp = TRUE;
  if (!IsActivatedVengefulBogSpiritZone(&zone))
    __builtin_trap();
}
#endif
