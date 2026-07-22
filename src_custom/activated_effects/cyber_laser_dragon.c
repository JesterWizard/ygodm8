#include "global.h"
#include "common-chax.h"
#include "card.h"
#include "cyber_laser_dragon.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

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
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  return gCardData_NEW[zone->id].atk >= gCardData_NEW[CYBER_LASER_DRAGON].atk
      || gCardData_NEW[zone->id].def >= gCardData_NEW[CYBER_LASER_DRAGON].atk;
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

static void DestroyTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  Duel_DestroyZone(zone, GraveyardDuelistForOpponentZone(targetRow), FALSE);
}

static void BeginCyberLaserDragonTargeting(void)
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
  gDuelCursor.state = DUEL_CURSOR_CYBER_LASER_DRAGON_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gMonEffect.row, targetRow);
}

static void ResolveCyberLaserDragonEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(CYBER_LASER_DRAGON, targetRow, targetCol))
    return;

  DestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateCYBER_LASER_DRAGON(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != CYBER_LASER_DRAGON)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindFirstTarget(&unusedRow, &unusedCol);
}

void ActivateCYBER_LASER_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_LASER_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginCyberLaserDragonTargeting();
    return;
  }

  ResolveCyberLaserDragonEffectForAi();
}

void TrySelectCyberLaserDragonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp
      || (gCardData_NEW[zone->id].atk < gCardData_NEW[CYBER_LASER_DRAGON].atk
          && gCardData_NEW[zone->id].def < gCardData_NEW[CYBER_LASER_DRAGON].atk)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelCyberLaserDragonTargeting(void)
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
