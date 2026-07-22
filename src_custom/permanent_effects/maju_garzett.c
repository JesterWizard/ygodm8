#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "maju_garzett.h"
#include "mini_card.h"
#include "summon_tribute.h"
#include "tribute.h"

extern struct DuelCard *gSetFinalStatZone;
extern unsigned char gNumTributes;

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

static u8 FixedMonsterCellIndex(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return (MAX_ZONES_IN_ROW - 1) - fixedCol;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return MAX_ZONES_IN_ROW + fixedCol;
  return 0xFF;
}

static u8 GetFixedCellIndexForZone(struct DuelCard *zone, u8 *cellIndex)
{
  u8 fixedRow;
  u8 fixedCol;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol) == FALSE)
    return FALSE;

  *cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);
  return TRUE;
}

// ram_map byte packing can leave u16 fields at odd EWRAM addresses;
// GBA halfword loads there return the high byte only (600 -> 2, 500 -> 1).
static u16 ReadStatU16(const u8 *bytes)
{
  return (u16)bytes[0] | ((u16)bytes[1] << 8);
}

static void WriteStatU16(u8 *bytes, u16 value)
{
  bytes[0] = (u8)value;
  bytes[1] = (u8)(value >> 8);
}

static u16 LoadTributeAtk(void)
{
  return ReadStatU16((const u8 *)&gMajuGarzettTributeAtk);
}

static void StoreTributeAtk(u16 atk)
{
  WriteStatU16((u8 *)&gMajuGarzettTributeAtk, atk);
}

static u16 LoadBoardAtk(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gMajuGarzettBoardAtk + ((u16)cellIndex * 2));
}

static void StoreBoardAtk(u8 cellIndex, u16 atk)
{
  WriteStatU16((u8 *)gMajuGarzettBoardAtk + ((u16)cellIndex * 2), atk);
  gMajuGarzettBoardActive[cellIndex] = TRUE;
}

static void ClearMajuGarzettTributeAccumulator(void)
{
  StoreTributeAtk(0);
}

static void ShowMajuGarzettActivationText(void)
{
  Duel_ShowEffectText(MAJU_GARZETT);
}

void SetMajuGarzettPendingSummon(u8 pending)
{
  if (!pending)
    ClearMajuGarzettTributeAccumulator();
  gMajuGarzettPendingSummon = pending;
}

void TryCaptureMajuGarzettTributeFromZone(struct DuelCard *zone)
{
  struct StatMod statMod;
  u32 nextAtk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  statMod.card = zone->id;
  statMod.field = gDuel.field;
  statMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&statMod);

  nextAtk = (u32)LoadTributeAtk() + (u32)gCardInfo.atk;
  StoreTributeAtk(nextAtk > 0xFFFF ? 0xFFFF : (u16)nextAtk);
}

void ClearMajuGarzettBoardStatsForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return;

  StoreBoardAtk(cellIndex, 0);
  gMajuGarzettBoardActive[cellIndex] = FALSE;
}

static void StoreMajuGarzettBoardStatsAt(u8 fixedRow, u8 fixedCol, u16 atk)
{
  u8 cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);

  if (cellIndex == 0xFF)
    return;

  StoreBoardAtk(cellIndex, atk);
}

u8 MajuGarzettZoneHasCustomStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id != MAJU_GARZETT)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;

  return gMajuGarzettBoardActive[cellIndex];
}

u8 MajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;
  if (!gMajuGarzettBoardActive[cellIndex])
    return FALSE;

  SetCardInfo(zone->id);
  gCardInfo.atk = LoadBoardAtk(cellIndex);
  return TRUE;
}

void FinishMajuGarzettTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u16 atk;

  if (zone == NULL || zone->id != MAJU_GARZETT)
    return;
  if (GetPendingSummonTributeCount() == 0 && gNumTributes == 0)
    return;

  atk = LoadTributeAtk();
  StoreMajuGarzettBoardStatsAt(fixedRow, fixedCol, atk);
  FlipCardFaceUp(zone);
  zone->unk4 = 1;
  ClearMajuGarzettTributeAccumulator();
  gMajuGarzettPendingSummon = FALSE;
  ClearPendingSummonTributeCount();
  ShowMajuGarzettActivationText();
  RefreshFieldMonsterStatOverlays();
}

unsigned char ShouldActivateMajuGarzett(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != MAJU_GARZETT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (GetPendingSummonTributeCount() == 0)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return !MajuGarzettZoneHasCustomStats(zone);
}

void ActivateMajuGarzett(void)
{
  u8 fixedRow;
  u8 fixedCol;
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  if (!MajuGarzettZoneHasCustomStats(zone))
    FinishMajuGarzettTributeSummon(zone, fixedRow, fixedCol);
  else
    zone->unk4 = 1;
}

void TryCaptureMajuGarzettAiTribute(void)
{
  u8 handRow;
  u8 handCol;
  u8 tributeRow;
  u8 tributeCol;
  struct DuelCard *handZone;
  struct DuelCard *tributeZone;

  if (!IsAiTributeSummonAction(sAI_Command.action))
    return;

  handRow = sAI_Command.zone1Position >> 4;
  handCol = sAI_Command.zone1Position & 0xF;
  handZone = gTurnZones[handRow][handCol];
  if (handZone->id != MAJU_GARZETT)
    return;

  SetMajuGarzettPendingSummon(TRUE);

  if (sAI_Command.action == AI_ACTION_1_TRIBUTE_SUMMON
      || sAI_Command.action == AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON) {
    tributeRow = sAI_Command.zone2Position >> 4;
    tributeCol = sAI_Command.zone2Position & 0xF;
    tributeZone = gTurnZones[tributeRow][tributeCol];
    TryCaptureMajuGarzettTributeFromZone(tributeZone);
    return;
  }

  if (sAI_Command.action == AI_ACTION_2_TRIBUTE_SUMMON
      || sAI_Command.action == AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON) {
    tributeRow = sAI_Command.zone2Position >> 4;
    tributeCol = sAI_Command.zone2Position & 0xF;
    tributeZone = gTurnZones[tributeRow][tributeCol];
    TryCaptureMajuGarzettTributeFromZone(tributeZone);

    tributeRow = sAI_Command.zone3Position >> 4;
    tributeCol = sAI_Command.zone3Position & 0xF;
    tributeZone = gTurnZones[tributeRow][tributeCol];
    TryCaptureMajuGarzettTributeFromZone(tributeZone);
  }
}

#if !defined(__GNUC__)
#error Maju Garzett board cell arrays must stay 0x1E bytes total in ram_map.s
#elif __GNUC__
typedef char maju_garzett_board_cell_bytes_check
    [(sizeof(gMajuGarzettBoardAtk) + sizeof(gMajuGarzettBoardActive)) == 0x1E ? 1 : -1];
#endif
