#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "card.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "the_tyrant_neptune.h"
#include "mini_card.h"
#include "summon_tribute.h"
#include "tribute.h"

extern unsigned char gNumTributes;
extern u8 gHideEffectText;

void UpdateDuelGfxExceptField(void);

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

static const u8 sNeptuneGyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

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

// ponytail: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
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
  return ReadStatU16((const u8 *)gTheTyrantNeptuneTributeTotals);
}

static u16 LoadTributeDef(void)
{
  return ReadStatU16((const u8 *)gTheTyrantNeptuneTributeTotals + 2);
}

static void StoreTributeTotals(u16 atk, u16 def)
{
  WriteStatU16((u8 *)gTheTyrantNeptuneTributeTotals, atk);
  WriteStatU16((u8 *)gTheTyrantNeptuneTributeTotals + 2, def);
}

static u16 LoadBoardAtk(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gTheTyrantNeptuneBoardAtk + ((u16)cellIndex * 2));
}

static u16 LoadBoardDef(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gTheTyrantNeptuneBoardDef + ((u16)cellIndex * 2));
}

static u16 LoadCopiedCardId(u8 cellIndex)
{
  return ReadStatU16((const u8 *)gTheTyrantNeptuneCopiedCardId + ((u16)cellIndex * 2));
}

static void StoreCopiedCardId(u8 cellIndex, u16 cardId)
{
  WriteStatU16((u8 *)gTheTyrantNeptuneCopiedCardId + ((u16)cellIndex * 2), cardId);
}

static u16 LoadTributeId(u8 index)
{
  return ReadStatU16((const u8 *)gTheTyrantNeptuneTributeIds + ((u16)index * 2));
}

static void StoreTributeId(u8 index, u16 cardId)
{
  WriteStatU16((u8 *)gTheTyrantNeptuneTributeIds + ((u16)index * 2), cardId);
}

static void StoreBoardStats(u8 cellIndex, u16 atk, u16 def)
{
  WriteStatU16((u8 *)gTheTyrantNeptuneBoardAtk + ((u16)cellIndex * 2), atk);
  WriteStatU16((u8 *)gTheTyrantNeptuneBoardDef + ((u16)cellIndex * 2), def);
  gTheTyrantNeptuneBoardActive[cellIndex] = TRUE;
}

static void ClearTheTyrantNeptuneTributeAccumulators(void)
{
  u8 i;

  StoreTributeTotals(0, 0);
  for (i = 0; i < THE_TYRANT_NEPTUNE_MAX_TRIBUTES; i++)
    StoreTributeId(i, CARD_NONE);
  gTheTyrantNeptuneTributeCount = 0;
}

static void ShowTheTyrantNeptuneActivationText(void)
{
  Duel_ShowEffectText(THE_TYRANT_NEPTUNE);
}

static u8 IsEffectMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color == EFFECT_CARD)
    return TRUE;
  /* Some effect monsters are Fusion/Ritual-colored but still have effects. */
  return gCardInfo.monsterEffect != 0;
}

/* Trunk list = Effect Monsters tributed for this summon (source of truth). */
static u8 LoadTributedEffectMonsterMenu(void)
{
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gTheTyrantNeptuneTributeCount; i++) {
    u16 cardId = LoadTributeId(i);

    if (!IsEffectMonsterCard(cardId))
      continue;

    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u16 PlayerPickCopiedEffectCard(void)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount;
  u8 j;
  u16 chosenId;

  /* gDeckMenu.cards is the player deck — save before overwriting for the picker. */
  DECKMENU_SAVE();

  menuCount = LoadTributedEffectMonsterMenu();
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return CARD_NONE;
  }

  /* Always open the trunk view, even for a single eligible tribute. */
  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sNeptuneGyPickLabels, ARRAY_COUNT(sNeptuneGyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  /* Read after DeckMenuSort — currentPos indexes the sorted gDeckMenu.cards. */
  chosenId = CARD_NONE;
  if (gDeckMenu.currentPos < gDeckMenu.cardCount)
    chosenId = gDeckMenu.cards[gDeckMenu.currentPos];

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 PickCopiedEffectCardForAi(void)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount;
  u8 j;
  u16 chosenId;

  DECKMENU_SAVE();

  menuCount = LoadTributedEffectMonsterMenu();
  chosenId = menuCount == 0 ? CARD_NONE : gDeckMenu.cards[0];

  DECKMENU_RESTORE();

  return chosenId;
}

static void TryCopyEffectFromTributedMonsters(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u8 cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);
  u16 chosenId = CARD_NONE;

  if (cellIndex == 0xFF)
    return;

  StoreCopiedCardId(cellIndex, CARD_NONE);

  if (gTheTyrantNeptuneTributeCount == 0)
    return;

  if (!gHideEffectText && WhoseTurn() == DUEL_PLAYER)
    chosenId = PlayerPickCopiedEffectCard();
  else
    chosenId = PickCopiedEffectCardForAi();

  if (chosenId != CARD_NONE)
    StoreCopiedCardId(cellIndex, chosenId);
}

void SetTheTyrantNeptunePendingSummon(u8 pending)
{
  /* Only clear on FALSE. Never clear on TRUE — placement calls Set(TRUE) after
   * tributes are already captured and must not wipe ATK/DEF / tribute ids. */
  if (!pending)
    ClearTheTyrantNeptuneTributeAccumulators();
  gTheTyrantNeptunePendingSummon = pending;
}

void TryCaptureTheTyrantNeptuneTributeFromZone(struct DuelCard *zone)
{
  u32 nextAtk;
  u32 nextDef;
  u16 cardId;

  /* Same as Maju Garzett: always record tributes; stale data is cleared when
   * tribute selection starts (Set(FALSE) then Set(TRUE) for Neptune). */
  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  cardId = zone->id;

  /* Printed original ATK/DEF only — not field/stage-modified combat stats. */
  SetCardInfo(cardId);

  nextAtk = (u32)LoadTributeAtk() + (u32)gCardInfo.atk;
  nextDef = (u32)LoadTributeDef() + (u32)gCardInfo.def;
  StoreTributeTotals(
      nextAtk > 0xFFFF ? 0xFFFF : (u16)nextAtk,
      nextDef > 0xFFFF ? 0xFFFF : (u16)nextDef);

  if (gTheTyrantNeptuneTributeCount < THE_TYRANT_NEPTUNE_MAX_TRIBUTES) {
    StoreTributeId(gTheTyrantNeptuneTributeCount, cardId);
    gTheTyrantNeptuneTributeCount++;
  }
}

void ClearTheTyrantNeptuneBoardStatsForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return;

  StoreBoardStats(cellIndex, 0, 0);
  StoreCopiedCardId(cellIndex, CARD_NONE);
  gTheTyrantNeptuneBoardActive[cellIndex] = FALSE;
}

static void StoreTheTyrantNeptuneBoardStatsAt(u8 fixedRow, u8 fixedCol, u16 atk, u16 def)
{
  u8 cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);

  if (cellIndex == 0xFF)
    return;

  StoreBoardStats(cellIndex, atk, def);
}

u8 TheTyrantNeptuneZoneHasCustomStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id != THE_TYRANT_NEPTUNE)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;

  return gTheTyrantNeptuneBoardActive[cellIndex];
}

u16 TheTyrantNeptune_GetCopiedCardId(struct DuelCard *zone)
{
  u8 cellIndex;
  u16 copied;

  if (zone == NULL)
    return CARD_NONE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return CARD_NONE;
  if (!gTheTyrantNeptuneBoardActive[cellIndex])
    return CARD_NONE;

  copied = LoadCopiedCardId(cellIndex);
  /* Normal Neptune, or identity-swapped to its copied effect monster. */
  if (zone->id != THE_TYRANT_NEPTUNE && zone->id != copied)
    return CARD_NONE;

  return copied;
}

u8 TheTyrantNeptune_HasCopiedEffect(struct DuelCard *zone)
{
  return TheTyrantNeptune_GetCopiedCardId(zone) != CARD_NONE;
}

u16 TheTyrantNeptune_HostCardId(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL)
    return CARD_NONE;
  if (zone->id == THE_TYRANT_NEPTUNE)
    return THE_TYRANT_NEPTUNE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return CARD_NONE;
  if (!gTheTyrantNeptuneBoardActive[cellIndex])
    return CARD_NONE;
  /* Identity-swapped: zone shows the copy, but the host is still Neptune. */
  if (LoadCopiedCardId(cellIndex) == zone->id)
    return THE_TYRANT_NEPTUNE;

  return CARD_NONE;
}

/* Temporarily treat Neptune as its copied monster so effect handlers match. */
u16 TheTyrantNeptune_BeginEffectIdentity(struct DuelCard *zone)
{
  u16 copied;
  u16 saved;

  if (zone == NULL || zone->id != THE_TYRANT_NEPTUNE)
    return CARD_NONE;

  copied = TheTyrantNeptune_GetCopiedCardId(zone);
  if (copied == CARD_NONE)
    return CARD_NONE;

  saved = zone->id;
  zone->id = copied;
  return saved;
}

void TheTyrantNeptune_EndEffectIdentity(struct DuelCard *zone, u16 savedId)
{
  if (zone == NULL || savedId == CARD_NONE)
    return;

  zone->id = savedId;
}

u8 TheTyrantNeptune_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (GetFixedCellIndexForZone(zone, &cellIndex) == FALSE)
    return FALSE;
  if (!gTheTyrantNeptuneBoardActive[cellIndex])
    return FALSE;

  /* Stats stay on Neptune even while effect identity is swapped to its copy. */
  if (zone->id != THE_TYRANT_NEPTUNE && LoadCopiedCardId(cellIndex) != zone->id)
    return FALSE;

  {
    u32 atk = LoadBoardAtk(cellIndex);
    u16 def = LoadBoardDef(cellIndex);
    u16 copied = LoadCopiedCardId(cellIndex);
    s8 stage;

    /* Registered passive/continuous bonuses for the copied effect card. */
    if (copied != CARD_NONE)
      atk = (u32)atk + (u32)Duel_CopiedPassiveAtkBonus(zone, copied);

    if (atk > 0xFFFF)
      atk = 0xFFFF;

    SetCardInfo(THE_TYRANT_NEPTUNE);
    /* Copied vanilla passives (e.g. Blade Knight) use tempStage/permStage. */
    stage = ComputeFinalStage(zone);
    gCardInfo.atk = Duel_StageModifiedStat((u16)atk, stage);
    gCardInfo.def = Duel_StageModifiedStat(def, stage);
  }
  return TRUE;
}

void FinishTheTyrantNeptuneTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u16 atk;
  u16 def;
  u8 hadTributes;

  if (zone == NULL || zone->id != THE_TYRANT_NEPTUNE)
    return;

  /* Require captured tribute data — gNumTributes alone used to show the popup
   * with 0/0 when capture was wiped before Finish. */
  atk = LoadTributeAtk();
  def = LoadTributeDef();
  hadTributes = gTheTyrantNeptuneTributeCount != 0 || atk != 0 || def != 0;
  if (!hadTributes)
    return;

  StoreTheTyrantNeptuneBoardStatsAt(fixedRow, fixedCol, atk, def);
  FlipCardFaceUp(zone);
  zone->unk4 = 1;
  ClearPendingSummonTributeCount();
  /* ponytail: draw Neptune on the field before popup / trunk picker. */
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  ShowTheTyrantNeptuneActivationText();
  TryCopyEffectFromTributedMonsters(zone, fixedRow, fixedCol);
  /* Clears tribute list and pending flag together. */
  SetTheTyrantNeptunePendingSummon(FALSE);
}

unsigned char ShouldActivateTheTyrantNeptune(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != THE_TYRANT_NEPTUNE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (GetPendingSummonTributeCount() == 0)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return !TheTyrantNeptuneZoneHasCustomStats(zone);
}

void ActivateTheTyrantNeptune(void)
{
  u8 fixedRow;
  u8 fixedCol;
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  if (!TheTyrantNeptuneZoneHasCustomStats(zone))
    FinishTheTyrantNeptuneTributeSummon(zone, fixedRow, fixedCol);
  else
    zone->unk4 = 1;
}

void TryCaptureTheTyrantNeptuneAiTribute(void)
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
  if (handZone->id != THE_TYRANT_NEPTUNE)
    return;

  SetTheTyrantNeptunePendingSummon(FALSE);
  SetTheTyrantNeptunePendingSummon(TRUE);

  if (sAI_Command.action != AI_ACTION_1_TRIBUTE_SUMMON
      && sAI_Command.action != AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON)
    return;

  tributeRow = sAI_Command.zone2Position >> 4;
  tributeCol = sAI_Command.zone2Position & 0xF;
  tributeZone = gTurnZones[tributeRow][tributeCol];
  TryCaptureTheTyrantNeptuneTributeFromZone(tributeZone);
}

#if !defined(__GNUC__)
#error The Tyrant Neptune board cell arrays must stay 0x46 bytes total in ram_map.s
#elif __GNUC__
typedef char the_tyrant_neptune_board_cell_bytes_check
    [(sizeof(gTheTyrantNeptuneBoardAtk) + sizeof(gTheTyrantNeptuneBoardDef)
      + sizeof(gTheTyrantNeptuneBoardActive)
      + sizeof(gTheTyrantNeptuneCopiedCardId)) == 0x46 ? 1 : -1];
#endif
