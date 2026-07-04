#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "the_grand_jupiter.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

extern u8 gHideEffectText;

static u8 JupiterHasLinkedEquipsForZone(const struct DuelCard *jupiterZone);
static u8 ControllerHasEmptyMonsterZone(u8 jupiterFixedRow);
static u8 AiPickEndPhaseEquipTarget(u8 *outRow, u8 *outCol);
static void BeginAbsorbTargeting(u8 originFixedRow, u8 originFixedCol);
static u8 JupiterFixedRowForZone(const struct DuelCard *zone, u8 *outCol);
static struct DuelCard *JupiterZoneForEquipSlot(u8 slotIndex);
static void RefreshGrandJupiterStatOverlays(void);

static void MarkGrandJupiterAbsorbUsedThisTurn(struct DuelCard *jupiterZone)
{
  if (jupiterZone == NULL)
    return;

  jupiterZone->unkThree = GRAND_JUPITER_ABSORB_USED;
  MarkMonsterEffectUsed(jupiterZone);
}

static void MarkGrandJupiterEndPhaseUsedThisTurn(struct DuelCard *jupiterZone)
{
  if (jupiterZone == NULL)
    return;

  jupiterZone->unk4 = GRAND_JUPITER_END_PHASE_USED;
}

static struct DuelCard *AbsorbJupiterZone(u8 *outFixedCol)
{
  struct DuelCard *zone;

  if (gDuelCursor.destY == PLAYER_MONSTER_ROW
      || gDuelCursor.destY == OPPONENT_MONSTER_ROW) {
    zone = gFixedZones[gDuelCursor.destY][gDuelCursor.destX];
    if (zone != NULL && zone->id == THE_GRAND_JUPITER) {
      *outFixedCol = gDuelCursor.destX;
      return zone;
    }
  }

  if (gMonEffect.id != THE_GRAND_JUPITER)
    return NULL;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return NULL;

  *outFixedCol = gMonEffect.zone;
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static u8 AbsorbJupiterFixedRow(u8 *outCol)
{
  struct DuelCard *zone = AbsorbJupiterZone(outCol);
  u8 fixedRow;

  if (zone == NULL)
    return DYNAMIC_EQUIP_COORD_INVALID;

  fixedRow = JupiterFixedRowForZone(zone, outCol);
  if (fixedRow != DYNAMIC_EQUIP_COORD_INVALID)
    return fixedRow;

  if (gMonEffect.id == THE_GRAND_JUPITER
      && (gMonEffect.row == PLAYER_MONSTER_ROW || gMonEffect.row == OPPONENT_MONSTER_ROW)) {
    *outCol = gMonEffect.zone;
    return gMonEffect.row;
  }

  return DYNAMIC_EQUIP_COORD_INVALID;
}

static u16 ReadStatU16(const u8 *bytes)
{
  return (u16)bytes[0] | ((u16)bytes[1] << 8);
}

static void WriteStatU16(u8 *bytes, u16 value)
{
  bytes[0] = (u8)value;
  bytes[1] = (u8)(value >> 8);
}

static u8 BackrowSlotIndex(u8 fixedBackrowRow, u8 fixedBackrowCol)
{
  if (fixedBackrowRow == OPPONENT_BACKROW)
    return fixedBackrowCol;
  if (fixedBackrowRow == PLAYER_BACKROW)
    return (u8)(MAX_ZONES_IN_ROW + fixedBackrowCol);
  return 0xFF;
}

static u8 BackrowCoordsFromSlotIndex(u8 slotIndex, u8 *outRow, u8 *outCol)
{
  if (slotIndex >= GRAND_JUPITER_BACKROW_SLOT_COUNT)
    return FALSE;

  if (slotIndex < MAX_ZONES_IN_ROW) {
    *outRow = OPPONENT_BACKROW;
    *outCol = slotIndex;
    return TRUE;
  }

  *outRow = PLAYER_BACKROW;
  *outCol = (u8)(slotIndex - MAX_ZONES_IN_ROW);
  return TRUE;
}

static u16 LoadEquipOriginalAtk(u8 slotIndex)
{
  return ReadStatU16(gGrandJupiterEquipOriginalAtk + ((u16)slotIndex * 2));
}

static u16 GetOriginalAtk(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE && cardId >= CUSTOM_CARD_START)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static u16 EquipSlotOriginalAtk(u8 slotIndex)
{
  u8 backrowRow;
  u8 backrowCol;
  struct DuelCard *equipZone;
  u16 stored;

  stored = LoadEquipOriginalAtk(slotIndex);
  if (stored != 0)
    return stored;

  if (!BackrowCoordsFromSlotIndex(slotIndex, &backrowRow, &backrowCol))
    return 0;

  equipZone = gFixedZones[backrowRow][backrowCol];
  if (equipZone == NULL || equipZone->id == CARD_NONE)
    return 0;

  return GetOriginalAtk(equipZone->id);
}

static u16 SumEquipOriginalAtkForJupiterZone(const struct DuelCard *jupiterZone)
{
  u8 slotIndex;
  u16 total = 0;

  if (jupiterZone == NULL)
    return 0;

  for (slotIndex = 0; slotIndex < GRAND_JUPITER_BACKROW_SLOT_COUNT; slotIndex++) {
    struct DuelCard *linkedJupiter;
    u16 atk;

    if (!gGrandJupiterEquipActive[slotIndex])
      continue;

    linkedJupiter = JupiterZoneForEquipSlot(slotIndex);
    if (linkedJupiter != jupiterZone)
      continue;

    atk = EquipSlotOriginalAtk(slotIndex);
    if (atk == 0)
      continue;

    total = (u16)Duel_ClampStat((u32)total + atk);
  }

  return total;
}

static void StoreEquipLink(u8 slotIndex, u16 originalAtk, u8 jupiterFixedRow,
                           u8 jupiterFixedCol)
{
  gGrandJupiterEquipActive[slotIndex] = TRUE;
  WriteStatU16(gGrandJupiterEquipOriginalAtk + ((u16)slotIndex * 2), originalAtk);
  gGrandJupiterEquipJupiterRow[slotIndex] = jupiterFixedRow;
  gGrandJupiterEquipJupiterCol[slotIndex] = jupiterFixedCol;
}

static void ClearEquipLink(u8 slotIndex)
{
  gGrandJupiterEquipActive[slotIndex] = FALSE;
  WriteStatU16(gGrandJupiterEquipOriginalAtk + ((u16)slotIndex * 2), 0);
  gGrandJupiterEquipJupiterRow[slotIndex] = 0xFF;
  gGrandJupiterEquipJupiterCol[slotIndex] = 0xFF;
}

u8 IsGrandJupiterEquipZone(u8 fixedBackrowRow, u8 fixedBackrowCol)
{
  u8 slotIndex = BackrowSlotIndex(fixedBackrowRow, fixedBackrowCol);

  if (slotIndex == 0xFF)
    return FALSE;

  return gGrandJupiterEquipActive[slotIndex] != FALSE;
}

void ClearTheGrandJupiterEquipSlot(u8 fixedBackrowRow, u8 fixedBackrowCol)
{
  u8 slotIndex = BackrowSlotIndex(fixedBackrowRow, fixedBackrowCol);
  struct DuelCard *jupiterZone;

  if (slotIndex == 0xFF || !gGrandJupiterEquipActive[slotIndex])
    return;

  jupiterZone = JupiterZoneForEquipSlot(slotIndex);
  ClearEquipLink(slotIndex);

  if (jupiterZone != NULL && jupiterZone->id == THE_GRAND_JUPITER)
    RefreshGrandJupiterStatOverlays();
}

static u8 JupiterFixedRowForZone(const struct DuelCard *zone, u8 *outCol)
{
  u8 fixedRow;

  if (Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, outCol))
    return fixedRow;

  return DYNAMIC_EQUIP_COORD_INVALID;
}

void ClearTheGrandJupiterEquipsForJupiterZone(struct DuelCard *jupiterZone)
{
  u8 slotIndex;

  if (jupiterZone == NULL || jupiterZone->id != THE_GRAND_JUPITER)
    return;

  for (slotIndex = 0; slotIndex < GRAND_JUPITER_BACKROW_SLOT_COUNT; slotIndex++) {
    u8 backrowRow;
    u8 backrowCol;
    struct DuelCard *equipZone;
    struct DuelCard *linkedJupiter;

    if (!gGrandJupiterEquipActive[slotIndex])
      continue;

    linkedJupiter = JupiterZoneForEquipSlot(slotIndex);
    if (linkedJupiter != jupiterZone)
      continue;

    if (!BackrowCoordsFromSlotIndex(slotIndex, &backrowRow, &backrowCol))
      continue;

    equipZone = gFixedZones[backrowRow][backrowCol];
    ClearEquipLink(slotIndex);
    if (equipZone != NULL && equipZone->id != CARD_NONE)
      ClearZoneAndSendMonToGraveyard2(equipZone, GetDuelistForZone(equipZone));
  }
}

void ResetTheGrandJupiterEquipState(void)
{
  u8 slotIndex;

  for (slotIndex = 0; slotIndex < GRAND_JUPITER_BACKROW_SLOT_COUNT; slotIndex++)
    ClearEquipLink(slotIndex);
}

void ResetTheGrandJupiterEndPhaseFlags(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != THE_GRAND_JUPITER)
        continue;

      zone->unkThree = 0;
      if (zone->unk4 == GRAND_JUPITER_END_PHASE_USED)
        zone->unk4 = 0;
    }
  }
}

static u8 ControllerBackrowForJupiter(u8 jupiterFixedRow)
{
  if (jupiterFixedRow == PLAYER_MONSTER_ROW)
    return PLAYER_BACKROW;
  if (jupiterFixedRow == OPPONENT_MONSTER_ROW)
    return OPPONENT_BACKROW;
  return DYNAMIC_EQUIP_COORD_INVALID;
}

static u8 ControllerMonsterRowForJupiter(u8 jupiterFixedRow)
{
  if (jupiterFixedRow == PLAYER_MONSTER_ROW)
    return PLAYER_MONSTER_ROW;
  if (jupiterFixedRow == OPPONENT_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;
  return DYNAMIC_EQUIP_COORD_INVALID;
}

static u8 OpponentMonsterRowForJupiter(u8 jupiterFixedRow)
{
  if (jupiterFixedRow == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;
  if (jupiterFixedRow == OPPONENT_MONSTER_ROW)
    return PLAYER_MONSTER_ROW;
  return DYNAMIC_EQUIP_COORD_INVALID;
}

static void RefreshGrandJupiterStatOverlays(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_RefreshMonsterStatOverlays();
  gHideEffectText = hideEffectText;
}

void ApplyTheGrandJupiterEquipAtkBonus(struct DuelCard *zone)
{
  u16 bonus;
  u32 atk;

  if (zone == NULL || zone->id != THE_GRAND_JUPITER || !ZoneShowsCombatStats(zone))
    return;

  bonus = SumEquipOriginalAtkForJupiterZone(zone);
  if (bonus == 0)
    return;

  atk = (u32)gCardInfo.atk + (u32)bonus;
  gCardInfo.atk = Duel_ClampStat(atk);
}

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 FindEmptyControllerBackrowCol(u8 jupiterFixedRow, u8 *outCol)
{
  u8 backrow = ControllerBackrowForJupiter(jupiterFixedRow);
  u8 col;

  if (backrow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[backrow][col]->id != CARD_NONE)
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 FieldHasAbsorbTarget(u8 jupiterFixedRow)
{
  u8 targetRow = OpponentMonsterRowForJupiter(jupiterFixedRow);
  u8 col;
  u8 unusedCol;

  if (targetRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  if (!FindEmptyControllerBackrowCol(jupiterFixedRow, &unusedCol))
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpMonsterTarget(gFixedZones[targetRow][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidAbsorbTargetZone(u8 fixedRow, u8 fixedCol)
{
  u8 jupiterCol;
  u8 jupiterFixedRow = AbsorbJupiterFixedRow(&jupiterCol);
  u8 targetRow;

  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  targetRow = OpponentMonsterRowForJupiter(jupiterFixedRow);
  if (fixedRow != targetRow)
    return FALSE;

  return IsFaceUpMonsterTarget(gFixedZones[fixedRow][fixedCol]);
}

static void AbsorbTargetMonster(u8 targetFixedRow, u8 targetFixedCol)
{
  u8 jupiterCol;
  struct DuelCard *jupiterZone = AbsorbJupiterZone(&jupiterCol);
  u8 jupiterFixedRow;
  struct DuelCard *targetZone = gFixedZones[targetFixedRow][targetFixedCol];
  u8 backrowRow;
  u8 backrowCol;
  u8 slotIndex;
  struct DuelCard *equipZone;
  u16 monsterId;
  u16 originalAtk;

  if (jupiterZone == NULL)
    return;

  jupiterFixedRow = JupiterFixedRowForZone(jupiterZone, &jupiterCol);
  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return;

  backrowRow = ControllerBackrowForJupiter(jupiterFixedRow);

  if (jupiterZone->id != THE_GRAND_JUPITER || !IsValidAbsorbTargetZone(targetFixedRow, targetFixedCol))
    return;

  if (!FindEmptyControllerBackrowCol(jupiterFixedRow, &backrowCol))
    return;

  slotIndex = BackrowSlotIndex(backrowRow, backrowCol);
  if (slotIndex == 0xFF)
    return;

  monsterId = targetZone->id;
  originalAtk = GetOriginalAtk(monsterId);
  equipZone = gFixedZones[backrowRow][backrowCol];

  equipZone->id = monsterId;
  equipZone->isFaceUp = TRUE;
  equipZone->isLocked = FALSE;
  equipZone->isDefending = FALSE;
  equipZone->unkTwo = 0;
  equipZone->unk4 = 0;
  equipZone->willChangeSides = FALSE;
  ResetTempStage(equipZone);
  ResetPermStage(equipZone);

  StoreEquipLink(slotIndex, originalAtk, jupiterFixedRow, jupiterCol);
  ClearZone(targetZone);

  RefreshGrandJupiterStatOverlays();
}

static u8 FindFirstAbsorbTarget(u8 *outRow, u8 *outCol)
{
  u8 jupiterCol;
  u8 jupiterFixedRow = AbsorbJupiterFixedRow(&jupiterCol);
  u8 targetRow;
  u8 col;

  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  targetRow = OpponentMonsterRowForJupiter(jupiterFixedRow);
  if (targetRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidAbsorbTargetZone(targetRow, col))
      continue;

    *outRow = targetRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 AiPickAbsorbTarget(u8 *outRow, u8 *outCol)
{
  u8 jupiterCol;
  u8 jupiterFixedRow = AbsorbJupiterFixedRow(&jupiterCol);
  u8 targetRow;
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  targetRow = OpponentMonsterRowForJupiter(jupiterFixedRow);
  if (targetRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidAbsorbTargetZone(targetRow, col))
      continue;

    zone = gFixedZones[targetRow][col];
    SetCardInfo(zone->id);
    ApplyFieldZoneStatsToCardInfo(zone);
    atk = gCardInfo.atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FindFirstAbsorbTarget(outRow, outCol);

  *outRow = targetRow;
  *outCol = bestCol;
  return TRUE;
}

static void BeginAbsorbTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;

  if (!FindFirstAbsorbTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_HAND, targetRow);
}

void TrySelectTheGrandJupiterAbsorbTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidAbsorbTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  AbsorbTargetMonster(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  DisplayCardInfoBar();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelTheGrandJupiterAbsorbTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static struct DuelCard *CurrentJupiterZone(void)
{
  if (gMonEffect.id == THE_GRAND_JUPITER)
    return gFixedZones[gMonEffect.row][gMonEffect.zone];

  if (gActiveEffect.cardId == THE_GRAND_JUPITER)
    return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  return NULL;
}

static u8 IsJupiterOnFieldForEffects(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_GRAND_JUPITER)
    return FALSE;

  return IsCardFaceUp((struct DuelCard *)zone) || zone->isDefending == FALSE;
}

static void ShowGrandJupiterPopup(u16 effectTextId)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(THE_GRAND_JUPITER, effectTextId);
  gHideEffectText = hideEffectText;
}

static struct DuelCard *JupiterZoneForEquipSlot(u8 slotIndex)
{
  u8 jupiterRow;
  u8 jupiterCol;

  if (slotIndex >= GRAND_JUPITER_BACKROW_SLOT_COUNT
      || !gGrandJupiterEquipActive[slotIndex])
    return NULL;

  jupiterRow = gGrandJupiterEquipJupiterRow[slotIndex];
  jupiterCol = gGrandJupiterEquipJupiterCol[slotIndex];
  if (jupiterRow != PLAYER_MONSTER_ROW && jupiterRow != OPPONENT_MONSTER_ROW)
    return NULL;

  return gFixedZones[jupiterRow][jupiterCol];
}

static u8 CanActivateTheGrandJupiterAbsorb(struct DuelCard *zone, u8 jupiterFixedRow)
{
  if (!IsJupiterOnFieldForEffects(zone) || zone->unkThree)
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 2)
    return FALSE;

  return FieldHasAbsorbTarget(jupiterFixedRow);
}

static u8 CanActivateTheGrandJupiterEndPhase(struct DuelCard *zone)
{
  u8 jupiterFixedRow;
  u8 jupiterCol;

  if (!IsJupiterOnFieldForEffects(zone) || zone->unk4 == GRAND_JUPITER_END_PHASE_USED)
    return FALSE;

  if (!JupiterHasLinkedEquipsForZone(zone))
    return FALSE;

  jupiterFixedRow = JupiterFixedRowForZone(zone, &jupiterCol);
  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  return ControllerHasEmptyMonsterZone(jupiterFixedRow);
}

unsigned char CanActivateTheGrandJupiter(void)
{
  struct DuelCard *zone;
  u8 jupiterFixedRow;
  u8 jupiterFixedCol;

  if (gMonEffect.id != THE_GRAND_JUPITER)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  jupiterFixedRow = JupiterFixedRowForZone(zone, &jupiterFixedCol);
  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  return CanActivateTheGrandJupiterAbsorb(zone, jupiterFixedRow);
}

void ActivateTheGrandJupiterEffect(void)
{
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  u8 jupiterFixedRow;
  u8 jupiterFixedCol;
  u8 originRow = gMonEffect.row;
  u8 originCol = gMonEffect.zone;

  jupiterFixedRow = JupiterFixedRowForZone(zone, &jupiterFixedCol);
  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return;

  if (!CanActivateTheGrandJupiterAbsorb(zone, jupiterFixedRow))
    return;

  ShowGrandJupiterPopup(CARD_EFFECT_TEXT_THE_GRAND_JUPITER_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 2, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  MarkGrandJupiterAbsorbUsedThisTurn(zone);

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginAbsorbTargeting(originRow, originCol);
    return;
  }

  {
    u8 targetRow;
    u8 targetCol;

    if (AiPickAbsorbTarget(&targetRow, &targetCol)) {
      AbsorbTargetMonster(targetRow, targetCol);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
    }
  }
}

static struct DuelCard *ActiveTurnEffectJupiterZone(void)
{
  return CurrentJupiterZone();
}

static u8 JupiterHasLinkedEquipsForZone(const struct DuelCard *jupiterZone)
{
  u8 slotIndex;

  if (jupiterZone == NULL)
    return FALSE;

  for (slotIndex = 0; slotIndex < GRAND_JUPITER_BACKROW_SLOT_COUNT; slotIndex++) {
    if (!gGrandJupiterEquipActive[slotIndex])
      continue;
    if (JupiterZoneForEquipSlot(slotIndex) == jupiterZone)
      return TRUE;
  }

  return FALSE;
}

static u8 ControllerHasEmptyMonsterZone(u8 jupiterFixedRow)
{
  u8 monsterRow = ControllerMonsterRowForJupiter(jupiterFixedRow);
  u8 turnRow;

  if (monsterRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  turnRow = Duel_FixedMonsterRowToTurnMonsterRow(monsterRow);
  return FirstEmptyZoneInRow(gTurnZones[turnRow]) >= 0;
}

static u8 IsValidEquippedMonsterSummon(u8 fixedBackrowRow, u8 fixedBackrowCol,
                                       struct DuelCard **outJupiterZone)
{
  u8 slotIndex;
  struct DuelCard *jupiterZone;

  if (!IsGrandJupiterEquipZone(fixedBackrowRow, fixedBackrowCol))
    return FALSE;

  slotIndex = BackrowSlotIndex(fixedBackrowRow, fixedBackrowCol);
  if (slotIndex == 0xFF)
    return FALSE;

  jupiterZone = JupiterZoneForEquipSlot(slotIndex);
  if (jupiterZone == NULL || jupiterZone->id != THE_GRAND_JUPITER)
    return FALSE;

  if (outJupiterZone != NULL)
    *outJupiterZone = jupiterZone;

  return TRUE;
}

static u8 FindFirstEndPhaseEquipTarget(const struct DuelCard *jupiterZone, u8 *outRow,
                                       u8 *outCol)
{
  u8 jupiterFixedRow;
  u8 jupiterCol;
  u8 backrow;
  u8 col;

  if (jupiterZone == NULL)
    return FALSE;

  jupiterFixedRow = JupiterFixedRowForZone(jupiterZone, &jupiterCol);
  if (jupiterFixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  backrow = ControllerBackrowForJupiter(jupiterFixedRow);
  if (backrow == DYNAMIC_EQUIP_COORD_INVALID)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u8 slotIndex;

    if (!IsGrandJupiterEquipZone(backrow, col))
      continue;

    slotIndex = BackrowSlotIndex(backrow, col);
    if (JupiterZoneForEquipSlot(slotIndex) != jupiterZone)
      continue;

    *outRow = backrow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void SpecialSummonEquippedMonster(u8 equipBackrowRow, u8 equipBackrowCol)
{
  struct DuelCard *jupiterZone;
  struct DuelCard *equipZone = gFixedZones[equipBackrowRow][equipBackrowCol];
  u8 controllerDuelist;
  u8 turnDuelist;
  u16 monsterId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!IsValidEquippedMonsterSummon(equipBackrowRow, equipBackrowCol, &jupiterZone))
    return;

  MarkGrandJupiterEndPhaseUsedThisTurn(jupiterZone);

  controllerDuelist = GetDuelistForZone(jupiterZone);
  turnDuelist = controllerDuelist == WhoseTurn() ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  monsterId = equipZone->id;

  ClearTheGrandJupiterEquipSlot(equipBackrowRow, equipBackrowCol);
  ClearZone(equipZone);

  if (Duel_SpecialSummonMonsterId(turnDuelist, monsterId, opts) != DUEL_ACTION_OK)
    return;

  RefreshGrandJupiterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 AiPickEndPhaseEquipTarget(u8 *outRow, u8 *outCol)
{
  struct DuelCard *jupiterZone = ActiveTurnEffectJupiterZone();

  if (jupiterZone == NULL)
    return FALSE;

  return FindFirstEndPhaseEquipTarget(jupiterZone, outRow, outCol);
}

u8 CanActivateGrandJupiterEquippedMonster(u8 fixedBackrowRow, u8 fixedBackrowCol)
{
  struct DuelCard *jupiterZone;

  if (!IsValidEquippedMonsterSummon(fixedBackrowRow, fixedBackrowCol, &jupiterZone))
    return FALSE;

  if (GetDuelistForZone(jupiterZone) != WhoseTurn())
    return FALSE;

  return CanActivateTheGrandJupiterEndPhase(jupiterZone);
}

void ActivateGrandJupiterEquippedMonster(u8 fixedBackrowRow, u8 fixedBackrowCol)
{
  if (!CanActivateGrandJupiterEquippedMonster(fixedBackrowRow, fixedBackrowCol))
    return;

  ShowGrandJupiterPopup(CARD_EFFECT_TEXT_THE_GRAND_JUPITER_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonEquippedMonster(fixedBackrowRow, fixedBackrowCol);
}

unsigned char ShouldActivateTheGrandJupiterTurnEffect(void)
{
  struct DuelCard *zone = ActiveTurnEffectJupiterZone();

  if (zone == NULL || zone->id != THE_GRAND_JUPITER)
    return FALSE;

  if (GetDuelistForZone(zone) == DUEL_PLAYER)
    return FALSE;

  return CanActivateTheGrandJupiterEndPhase(zone);
}

void ActivateTheGrandJupiterTurnEffect(void)
{
  struct DuelCard *zone = ActiveTurnEffectJupiterZone();
  u8 equipRow;
  u8 equipCol;

  if (zone == NULL)
    return;

  if (!AiPickEndPhaseEquipTarget(&equipRow, &equipCol))
    return;

  SpecialSummonEquippedMonster(equipRow, equipCol);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheGrandJupiter_SelfCheck(void)
{
  struct DuelCard *jupiterZone = gFixedZones[PLAYER_MONSTER_ROW][0];
  u16 zoneEaterAtk = GetOriginalAtk(ZONE_EATER);
  u16 bonus;

  if (zoneEaterAtk == 0)
    while (1)
      ;

  gGrandJupiterEquipActive[0] = TRUE;
  gGrandJupiterEquipJupiterRow[0] = PLAYER_MONSTER_ROW;
  gGrandJupiterEquipJupiterCol[0] = 0;
  WriteStatU16(gGrandJupiterEquipOriginalAtk, zoneEaterAtk);

  bonus = SumEquipOriginalAtkForJupiterZone(jupiterZone);
  ResetTheGrandJupiterEquipState();

  if (bonus != zoneEaterAtk)
    while (1)
      ;
}
#endif
