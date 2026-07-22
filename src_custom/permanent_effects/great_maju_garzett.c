#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "great_maju_garzett.h"
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
  return ReadStatU16((const u8 *)gGreatMajuGarzettTributeTotals);
}

static u16 LoadTributeDef(void)
{
  return ReadStatU16((const u8 *)gGreatMajuGarzettTributeTotals + 2);
}

static void StoreTributeTotals(u16 atk, u16 def)
{
  WriteStatU16((u8 *)gGreatMajuGarzettTributeTotals, atk);
  WriteStatU16((u8 *)gGreatMajuGarzettTributeTotals + 2, def);
}

static u16 LoadBoardAtk(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gGreatMajuGarzettBoardAtk + ((u16)cellIndex * 2));
}

static u16 LoadBoardDef(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gGreatMajuGarzettBoardDef + ((u16)cellIndex * 2));
}

static void StoreBoardStats(u8 cellIndex, u16 atk, u16 def)
{
  WriteStatU16((u8 *)gGreatMajuGarzettBoardAtk + ((u16)cellIndex * 2), atk);
  WriteStatU16((u8 *)gGreatMajuGarzettBoardDef + ((u16)cellIndex * 2), def);
  gGreatMajuGarzettBoardActive[cellIndex] = TRUE;
}

static void ClearGreatMajuGarzettTributeAccumulators(void)
{
  StoreTributeTotals(0, 0);
}

static void ShowGreatMajuGarzettActivationText(void)
{
  Duel_ShowEffectText(GREAT_MAJU_GARZETT);
}

static u16 DoubleTributeStat(u16 stat)
{
  u32 doubled = (u32)stat * 2;

  if (doubled > 0xFFFF)
    return 0xFFFF;
  return (u16)doubled;
}

void SetGreatMajuGarzettPendingSummon(u8 pending)
{
  if (!pending)
    ClearGreatMajuGarzettTributeAccumulators();
  gGreatMajuGarzettPendingSummon = pending;
}

void TryCaptureGreatMajuGarzettTributeFromZone(struct DuelCard *zone)
{
  struct StatMod statMod;
  u32 nextAtk;
  u32 nextDef;

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
  nextDef = (u32)LoadTributeDef() + (u32)gCardInfo.def;
  StoreTributeTotals(
      nextAtk > 0xFFFF ? 0xFFFF : (u16)nextAtk,
      nextDef > 0xFFFF ? 0xFFFF : (u16)nextDef);
}

void ClearGreatMajuGarzettBoardStatsForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return;

  StoreBoardStats(cellIndex, 0, 0);
  gGreatMajuGarzettBoardActive[cellIndex] = FALSE;
}

void StoreGreatMajuGarzettBoardStats(struct DuelCard *zone, u16 atk, u16 def)
{
  u8 cellIndex;

  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return;

  StoreBoardStats(cellIndex, atk, def);
}

static void StoreGreatMajuGarzettBoardStatsAt(u8 fixedRow, u8 fixedCol, u16 atk, u16 def)
{
  u8 cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);

  if (cellIndex == 0xFF)
    return;

  StoreBoardStats(cellIndex, atk, def);
}

u8 GreatMajuGarzettZoneHasCustomStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id != GREAT_MAJU_GARZETT)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;

  return gGreatMajuGarzettBoardActive[cellIndex];
}

u8 GreatMajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;
  if (!gGreatMajuGarzettBoardActive[cellIndex])
    return FALSE;

  SetCardInfo(zone->id);
  gCardInfo.atk = LoadBoardAtk(cellIndex);
  gCardInfo.def = LoadBoardDef(cellIndex);
  return TRUE;
}

void FinishGreatMajuGarzettTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u16 atk;
  u16 def;

  if (zone == NULL || zone->id != GREAT_MAJU_GARZETT)
    return;
  if (GetPendingSummonTributeCount() == 0 && gNumTributes == 0)
    return;

  atk = DoubleTributeStat(LoadTributeAtk());
  def = DoubleTributeStat(LoadTributeDef());
  StoreGreatMajuGarzettBoardStatsAt(fixedRow, fixedCol, atk, def);
  FlipCardFaceUp(zone);
  zone->unk4 = 1;
  ClearGreatMajuGarzettTributeAccumulators();
  gGreatMajuGarzettPendingSummon = FALSE;
  ClearPendingSummonTributeCount();
  ShowGreatMajuGarzettActivationText();
  RefreshFieldMonsterStatOverlays();
}

unsigned char ShouldActivateGreatMajuGarzett(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != GREAT_MAJU_GARZETT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (GetPendingSummonTributeCount() == 0)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return !GreatMajuGarzettZoneHasCustomStats(zone);
}

void ActivateGreatMajuGarzett(void)
{
  u8 fixedRow;
  u8 fixedCol;
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  if (!GreatMajuGarzettZoneHasCustomStats(zone))
    FinishGreatMajuGarzettTributeSummon(zone, fixedRow, fixedCol);
  else
    zone->unk4 = 1;
}

void TryCaptureGreatMajuGarzettAiTribute(void)
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
  if (handZone->id != GREAT_MAJU_GARZETT)
    return;

  SetGreatMajuGarzettPendingSummon(TRUE);

  if (sAI_Command.action != AI_ACTION_1_TRIBUTE_SUMMON
      && sAI_Command.action != AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON)
    return;

  tributeRow = sAI_Command.zone2Position >> 4;
  tributeCol = sAI_Command.zone2Position & 0xF;
  tributeZone = gTurnZones[tributeRow][tributeCol];
  TryCaptureGreatMajuGarzettTributeFromZone(tributeZone);
}

#if !defined(__GNUC__)
#error Great Maju Garzett board cell arrays must stay 0x32 bytes total in ram_map.s
#elif __GNUC__
typedef char great_maju_board_cell_bytes_check
    [(sizeof(gGreatMajuGarzettBoardAtk) + sizeof(gGreatMajuGarzettBoardDef)
      + sizeof(gGreatMajuGarzettBoardActive)) == 0x32 ? 1 : -1];
#endif
