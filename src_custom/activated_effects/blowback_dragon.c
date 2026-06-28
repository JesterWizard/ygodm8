#include "global.h"
#include "common-chax.h"
#include "blowback_dragon.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define BLOWBACK_DRAGON_COIN_FLIPS 3
#define BLOWBACK_DRAGON_HEADS_TO_DESTROY 2

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 OpponentControlsRow(u8 fixedRow)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW;

  return fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW;
}

static u8 GraveyardDuelistForOpponentZone(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!OpponentControlsRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FindFirstTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    if (!OpponentControlsRow(row))
      continue;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 CountCoinHeads(u8 flips)
{
  u8 i;
  u8 heads = 0;

  for (i = 0; i < flips; i++) {
    if (RandRangeU8(0, 1) == 1)
      heads++;
  }

  return heads;
}

static void DestroyTargetIfCoinSucceeds(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (CountCoinHeads(BLOWBACK_DRAGON_COIN_FLIPS) < BLOWBACK_DRAGON_HEADS_TO_DESTROY)
    return;

  Duel_DestroyZone(zone, GraveyardDuelistForOpponentZone(targetRow), FALSE);
}

static void BeginBlowbackDragonTargeting(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.state = DUEL_CURSOR_BLOWBACK_DRAGON_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gMonEffect.row, targetRow);
}

static void ResolveBlowbackDragonEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  DestroyTargetIfCoinSucceeds(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateBLOWBACK_DRAGON(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != BLOWBACK_DRAGON)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindFirstTarget(&unusedRow, &unusedCol);
}

void ActivateBLOWBACK_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(BLOWBACK_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginBlowbackDragonTargeting();
    return;
  }

  ResolveBlowbackDragonEffectForAi();
}

void TrySelectBlowbackDragonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyTargetIfCoinSucceeds(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelBlowbackDragonTargeting(void)
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
