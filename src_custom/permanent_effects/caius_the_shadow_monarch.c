#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"
#include "caius_the_shadow_monarch.h"

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

static u8 IsValidCaiusTargetZone(u8 fixedRow, u8 fixedCol, u8 originFixedRow,
                                 u8 originFixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (IsSameFixedZone(fixedRow, fixedCol, originFixedRow, originFixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone->id != CARD_NONE;
}

static u8 FindFirstCaiusTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidCaiusTargetZone(row, col, originFixedRow, originFixedCol))
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

static u8 PickAiCaiusTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
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

      if (!IsValidCaiusTargetZone(row, col, originFixedRow, originFixedCol))
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

  return FindFirstCaiusTarget(originFixedRow, originFixedCol, outRow, outCol);
}

static u8 GetDuelistForFixedZone(u8 fixedRow)
{
  if (fixedRow == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;
  return 0xFF;
}

static u8 IsDarkAttribute(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static void BanishTargetAndBurn(u8 targetRow, u8 targetCol)
{
  struct DuelCard *target = gFixedZones[targetRow][targetCol];
  u8 duelist;
  u8 wasDark = IsDarkAttribute(target->id);

  duelist = GetDuelistForFixedZone(targetRow);
  if (duelist == 0xFF)
    return;

  Duel_DestroyZone(target, duelist, FALSE);

  if (wasDark)
    Duel_ChangeLp(INACTIVE_DUELIST, -1000, FALSE);

  NotifyDynamicEquipFieldChanged();
}

static void MarkCaiusEffectUsed(u8 originFixedRow, u8 originFixedCol)
{
  gFixedZones[originFixedRow][originFixedCol]->unk4 = 1;
}

static void ShowCaiusActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_ShowEffectTextTyped(CAIUS_THE_SHADOW_MONARCH, 8);
  gHideEffectText = hideEffectText;
}

u8 FieldHasCaiusTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  return FindFirstCaiusTarget(originFixedRow, originFixedCol, &row, &col);
}

unsigned char ShouldActivateCaiusTheShadowMonarch(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != CAIUS_THE_SHADOW_MONARCH)
    return FALSE;

  if (GetPendingTributeSummonCardId() != CAIUS_THE_SHADOW_MONARCH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return FieldHasCaiusTarget(gActiveEffect.turnRow, gActiveEffect.col);
}

void BeginCaiusTheShadowMonarchTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstCaiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_CAIUS_THE_SHADOW_MONARCH_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

static void ResolveCaiusEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiCaiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  BanishTargetAndBurn(targetRow, targetCol);
  MarkCaiusEffectUsed(originFixedRow, originFixedCol);
}

void TrySelectCaiusTheShadowMonarchTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidCaiusTargetZone(targetRow, targetCol, originRow, originCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  BanishTargetAndBurn(targetRow, targetCol);
  MarkCaiusEffectUsed(originRow, originCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelCaiusTheShadowMonarchTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  MarkCaiusEffectUsed(gDuelCursor.destY, gDuelCursor.destX);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateCaiusTheShadowMonarch(void)
{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  ShowCaiusActivationText();

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW) {
    BeginCaiusTheShadowMonarchTargeting(originRow, originCol);
    return;
  }

  ResolveCaiusEffectForAi(originRow, originCol);
}
