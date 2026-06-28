#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"
#include "zaborg_the_thunder_monarch.h"

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

static u8 IsValidZaborgTargetZone(u8 fixedRow, u8 fixedCol, u8 originFixedRow,
                                  u8 originFixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (IsSameFixedZone(fixedRow, fixedCol, originFixedRow, originFixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstZaborgTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidZaborgTargetZone(row, col, originFixedRow, originFixedCol))
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

static u8 PickAiZaborgTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                             u8 *outCol)
{
  u8 row;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidZaborgTargetZone(row, col, originFixedRow, originFixedCol))
        continue;

      zone = gFixedZones[row][col];
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

  return FindFirstZaborgTarget(originFixedRow, originFixedCol, outRow, outCol);
}

static void DestroyZaborgTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *target = gFixedZones[targetRow][targetCol];
  u8 duelist = GetDuelistForZone(target);

  if (duelist == 0xFF)
    return;

  Duel_DestroyZone(target, duelist, FALSE);
  NotifyDynamicEquipFieldChanged();
}

static void MarkZaborgEffectUsed(u8 originFixedRow, u8 originFixedCol)
{
  gFixedZones[originFixedRow][originFixedCol]->unk4 = 1;
}

static void ShowZaborgActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_ShowEffectTextTyped(ZABORG_THE_THUNDER_MONARCH, 8);
  gHideEffectText = hideEffectText;
}

u8 FieldHasZaborgTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  return FindFirstZaborgTarget(originFixedRow, originFixedCol, &row, &col);
}

unsigned char ShouldActivateZaborgTheThunderMonarch(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ZABORG_THE_THUNDER_MONARCH)
    return FALSE;

  if (GetPendingTributeSummonCardId() != ZABORG_THE_THUNDER_MONARCH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return FieldHasZaborgTarget(gActiveEffect.turnRow, gActiveEffect.col);
}

void BeginZaborgTheThunderMonarchTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstZaborgTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_ZABORG_THE_THUNDER_MONARCH_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

static void ResolveZaborgEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiZaborgTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ZABORG_THE_THUNDER_MONARCH, targetRow, targetCol))
    return;

  DestroyZaborgTarget(targetRow, targetCol);
  MarkZaborgEffectUsed(originFixedRow, originFixedCol);
}

void TrySelectZaborgTheThunderMonarchTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidZaborgTargetZone(targetRow, targetCol, originRow, originCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyZaborgTarget(targetRow, targetCol);
  MarkZaborgEffectUsed(originRow, originCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelZaborgTheThunderMonarchTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  MarkZaborgEffectUsed(gDuelCursor.destY, gDuelCursor.destX);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateZaborgTheThunderMonarch(void)
{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  ShowZaborgActivationText();

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW) {
    BeginZaborgTheThunderMonarchTargeting(originRow, originCol);
    return;
  }

  ResolveZaborgEffectForAi(originRow, originCol);
}
