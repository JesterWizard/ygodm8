#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_magician_knight.h"
#include "dynamic_equip.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void SetCursorToCardDest(void);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsSameFixedZone(u8 rowA, u8 colA, u8 rowB, u8 colB)
{
  return rowA == rowB && colA == colB;
}

static u8 IsValidDarkMagicianKnightTargetZone(u8 fixedRow, u8 fixedCol, u8 originFixedRow,
                                              u8 originFixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  if (IsSameFixedZone(fixedRow, fixedCol, originFixedRow, originFixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone->id != CARD_NONE;
}

static u8 FindFirstDarkMagicianKnightTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                            u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidDarkMagicianKnightTargetZone(row, col, originFixedRow, originFixedCol))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u16 GetZoneAttackPoints(struct DuelCard *zone)
{
  ApplyFieldZoneStatsToCardInfo(zone);
  return gCardInfo.atk;
}

static u8 PickAiDarkMagicianKnightTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                         u8 *outCol)
{
  u8 row;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (row = OPPONENT_BACKROW; row <= OPPONENT_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidDarkMagicianKnightTargetZone(row, col, originFixedRow, originFixedCol))
        continue;

      zone = gFixedZones[row][col];
      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      atk = GetZoneAttackPoints(zone);
      if (bestRow == 0xFF || atk > bestAtk) {
        bestRow = row;
        bestCol = col;
        bestAtk = atk;
      }
    }
  }

  if (bestRow != 0xFF) {
    *outRow = bestRow;
    *outCol = bestCol;
    return TRUE;
  }

  for (row = OPPONENT_BACKROW; row <= OPPONENT_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidDarkMagicianKnightTargetZone(row, col, originFixedRow, originFixedCol))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FindFirstDarkMagicianKnightTarget(originFixedRow, originFixedCol, outRow, outCol);
}

static void DestroyDarkMagicianKnightTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *target = gFixedZones[targetRow][targetCol];
  u8 duelist = GetDuelistForZone(target);

  if (duelist == 0xFF)
    return;

  ClearZoneAndSendMonToGraveyard(target, duelist);
  NotifyDynamicEquipFieldChanged();
}

static void MarkDarkMagicianKnightEffectUsed(u8 originFixedRow, u8 originFixedCol)
{
  gFixedZones[originFixedRow][originFixedCol]->unk4 = 1;
}

static void ShowDarkMagicianKnightActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = DARK_MAGICIAN_KNIGHT;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;
}

u8 FieldHasDarkMagicianKnightTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  return FindFirstDarkMagicianKnightTarget(originFixedRow, originFixedCol, &row, &col);
}

unsigned char ShouldActivateDarkMagicianKnight(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != DARK_MAGICIAN_KNIGHT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return FieldHasDarkMagicianKnightTarget(gActiveEffect.turnRow, gActiveEffect.col);
}

void BeginDarkMagicianKnightTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDarkMagicianKnightTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

static void ResolveDarkMagicianKnightEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiDarkMagicianKnightTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  DestroyDarkMagicianKnightTarget(targetRow, targetCol);
  MarkDarkMagicianKnightEffectUsed(originFixedRow, originFixedCol);
}

void TrySelectDarkMagicianKnightTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidDarkMagicianKnightTargetZone(targetRow, targetCol, originRow, originCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyDarkMagicianKnightTarget(targetRow, targetCol);
  MarkDarkMagicianKnightEffectUsed(originRow, originCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelDarkMagicianKnightTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  MarkDarkMagicianKnightEffectUsed(gDuelCursor.destY, gDuelCursor.destX);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateDarkMagicianKnight(void)
{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  ShowDarkMagicianKnightActivationText();

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW) {
    BeginDarkMagicianKnightTargeting(originRow, originCol);
    return;
  }

  ResolveDarkMagicianKnightEffectForAi(originRow, originCol);
}
