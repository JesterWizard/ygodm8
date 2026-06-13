#include "global.h"
#include "common-chax.h"
#include "riryoku.h"
#include "mini_card.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void ResetCardEffectTextData(void);
void SetCardEffectTextType(u8);
void ActivateCardEffectText(void);

static u8 IsMonsterFixedRow(u8 fixedRow)
{
  return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == PLAYER_MONSTER_ROW;
}

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static s16 *GetRiryokuAtkDeltaPtr(const struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= MAX_DUEL_BOARD_CELLS)
    return NULL;

  return &gRiryokuAtkDelta[index];
}

void ClearRiryokuAtkDeltaForZone(const struct DuelCard *zone)
{
  s16 *delta = GetRiryokuAtkDeltaPtr(zone);

  if (delta != NULL)
    *delta = 0;
}

void ClearAllRiryokuAtkDeltas(void)
{
  u16 i;

  for (i = 0; i < MAX_DUEL_BOARD_CELLS; i++)
    gRiryokuAtkDelta[i] = 0;
}

void AddRiryokuAtkDelta(struct DuelCard *zone, s16 amount)
{
  s16 *delta = GetRiryokuAtkDeltaPtr(zone);
  s32 updated;

  if (delta == NULL || amount == 0)
    return;

  updated = (s32)(*delta) + (s32)amount;
  if (updated > 0x7FFF)
    updated = 0x7FFF;
  else if (updated < -0x8000)
    updated = -0x8000;

  *delta = (s16)updated;
}

void ApplyRiryokuAtkDeltaToCardInfo(const struct DuelCard *zone)
{
  const s16 *delta = GetRiryokuAtkDeltaPtr(zone);
  s32 atk;

  if (delta == NULL || *delta == 0)
    return;

  atk = (s32)gCardInfo.atk + (s32)(*delta);
  if (atk <= 0)
    gCardInfo.atk = 0;
  else if (atk > 0xFFFE)
    gCardInfo.atk = 0xFFFE;
  else
    gCardInfo.atk = (u16)atk;
}

static u8 IsRiryokuVisibleMonsterTarget(struct DuelCard *zone)
{
  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position monsters stay isFaceUp=0 until end-of-turn FlipAtkPosCardsFaceUp. */
  return zone->isDefending == FALSE;
}

static u8 IsValidRiryokuMonsterTarget(u8 fixedRow, u8 fixedCol, u8 excludeRow, u8 excludeCol)
{
  struct DuelCard *zone;

  if (!IsMonsterFixedRow(fixedRow))
    return FALSE;

  if (excludeRow != 0xFF && fixedRow == excludeRow && fixedCol == excludeCol)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (!IsRiryokuVisibleMonsterTarget(zone))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstRiryokuMonsterTarget(u8 excludeRow, u8 excludeCol, u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidRiryokuMonsterTarget(row, col, excludeRow, excludeCol))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 CountRiryokuMonsterTargets(u8 excludeRow, u8 excludeCol)
{
  u8 row;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidRiryokuMonsterTarget(row, col, excludeRow, excludeCol))
        count++;
    }
  }

  return count;
}

static u16 GetMonsterAtkOnField(struct DuelCard *zone)
{
  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  SetFinalStat(&gStatMod);
  return gCardInfo.atk;
}

u8 IsRiryokuCard(u16 cardId)
{
  return cardId == RIRYOKU;
}

u8 FieldHasRiryokuTarget(u8 originFixedRow, u8 originFixedCol)
{
  (void)originFixedRow;
  (void)originFixedCol;
  return CountRiryokuMonsterTargets(0xFF, 0xFF) >= 2;
}

void BeginRiryokuTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstRiryokuMonsterTarget(0xFF, 0xFF, &targetRow, &targetCol))
    return;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(1);
    gCardEffectTextData.cardId = RIRYOKU;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_RIRYOKU_SOURCE;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectRiryokuSourceTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 nextRow;
  u8 nextCol;

  if (!IsValidRiryokuMonsterTarget(targetRow, targetCol, 0xFF, 0xFF)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (CountRiryokuMonsterTargets(targetRow, targetCol) == 0) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gRiryokuSourceRow = targetRow;
  gRiryokuSourceCol = targetCol;

  if (!FindFirstRiryokuMonsterTarget(targetRow, targetCol, &nextRow, &nextCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_RIRYOKU_RECIPIENT;
  gDuelCursor.currentY = nextRow;
  gDuelCursor.currentX = nextCol;
  DisplayCardInfoBar();
  sub_8041E70(targetRow, nextRow);
}

void TrySelectRiryokuRecipientTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidRiryokuMonsterTarget(targetRow, targetCol, gRiryokuSourceRow, gRiryokuSourceCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gRiryokuRecipientRow = targetRow;
  gRiryokuRecipientCol = targetCol;

  gSpellEffectData.id = RIRYOKU;
  gSpellEffectData.row1 = gRiryokuSourceRow;
  gSpellEffectData.col1 = gRiryokuSourceCol;
  gSpellEffectData.row2 = gDuelCursor.destY;
  gSpellEffectData.col2 = gDuelCursor.destX;
  ActivateSpellEffect();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelRiryokuTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectRiryoku(void)
{
  struct DuelCard *source = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *recipient = gFixedZones[gRiryokuRecipientRow][gRiryokuRecipientCol];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u16 currentAtk;
  s16 lostAtk;

  if (!IsValidRiryokuMonsterTarget(gSpellEffectData.row1, gSpellEffectData.col1, 0xFF, 0xFF)
      || !IsValidRiryokuMonsterTarget(gRiryokuRecipientRow, gRiryokuRecipientCol,
                                      gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    currentAtk = GetMonsterAtkOnField(source);
    lostAtk = (s16)(currentAtk / 2);

    if (lostAtk > 0) {
      AddRiryokuAtkDelta(source, -lostAtk);
      AddRiryokuAtkDelta(recipient, lostAtk);
      RefreshFieldMonsterStatOverlays();
    }

    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  } else {
    ActivateTrapEffect(0);
  }
}
