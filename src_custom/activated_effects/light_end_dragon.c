#include "global.h"
#include "common-chax.h"
#include "light_end_dragon.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define LIGHT_END_DEF_REDUCTION (-1500)

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void SetCursorToCardDest(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(u8);
void RefreshFieldMonsterStatOverlays(void);

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

void ClearLightEndDragonDefDeltas(void)
{
  u16 i;

  for (i = 0; i < MAX_DUEL_BOARD_CELLS; i++)
    gLightEndDragonDefDelta[i] = 0;
}

void ApplyLightEndDragonDefDeltaToCardInfo(const struct DuelCard *zone)
{
  const s16 *delta;
  s32 stat;

  if (zone == NULL)
    return;

  {
    u16 index = GetDuelBoardCellIndex(zone);
    if (index >= MAX_DUEL_BOARD_CELLS)
      return;
    delta = &gLightEndDragonDefDelta[index];
  }

  if (*delta == 0)
    return;

  stat = (s32)gCardInfo.atk + (s32)(*delta);
  if (stat <= 0)
    gCardInfo.atk = 0;
  else if (stat > 0xFFFE)
    gCardInfo.atk = 0xFFFE;
  else
    gCardInfo.atk = (u16)stat;

  stat = (s32)gCardInfo.def + (s32)(*delta);
  if (stat <= 0)
    gCardInfo.def = 0;
  else if (stat > 0xFFFE)
    gCardInfo.def = 0xFFFE;
  else
    gCardInfo.def = (u16)stat;
}

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;
  return PLAYER_MONSTER_ROW;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OpponentMonsterRow(), col))
      return TRUE;
  }
  return FALSE;
}

static u8 FindFirstTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OpponentMonsterRow(), col)) {
      *outCol = col;
      return TRUE;
    }
  }
  return FALSE;
}

static void ResolveEffect(u8 targetRow, u8 targetCol)
{
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;
  struct DuelCard *selfZone = gFixedZones[originRow][originCol];
  struct DuelCard *targetZone = gFixedZones[targetRow][targetCol];

  if (selfZone != NULL && selfZone->id == LIGHT_END_DRAGON)
    DecrementPermStage(selfZone);

  if (targetZone != NULL && targetZone->id != CARD_NONE) {
    u16 index = GetDuelBoardCellIndex(targetZone);

    if (index < MAX_DUEL_BOARD_CELLS)
      gLightEndDragonDefDelta[index] = LIGHT_END_DEF_REDUCTION;
  }

  RefreshFieldMonsterStatOverlays();

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void ResolveForAi(void)
{
  u8 targetCol;

  if (!FindFirstTarget(&targetCol))
    return;

  ResolveEffect(OpponentMonsterRow(), targetCol);
}

unsigned char CanActivateLIGHT_END_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LIGHT_END_DRAGON)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateLIGHT_END_DRAGONEffect(void)
{
  u8 targetCol;

  Duel_ShowEffectTextTyped(LIGHT_END_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (!FindFirstTarget(&targetCol))
      return;

    PlayMusic(SFX_SELECT);
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    gDuelCursor.state = DUEL_CURSOR_LIGHT_END_DRAGON_TARGET;
    gDuelCursor.currentY = OpponentMonsterRow();
    gDuelCursor.currentX = targetCol;
    DisplayCardInfoBar();
    sub_8041E70(gMonEffect.row, OpponentMonsterRow());
    return;
  }

  ResolveForAi();
}

void TrySelectLightEndDragonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveEffect(targetRow, targetCol);
}

void CancelLightEndDragonTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}
