#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpies_pet_baby_dragon.h"
#include "monster_effect_usage.h"
#include "configs/runtime.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static const char sHarpieArchetypeName[] APPEND_RODATA = "Harpie";

static u8 CountOtherHarpieOnRow(u8 fixedRow, u16 excludeId)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];
    if (zone != NULL && zone->id != CARD_NONE && zone->isFaceUp
        && zone->id != excludeId
        && Duel_CardNameContains(zone->id, sHarpieArchetypeName)) {
      count++;
    }
  }

  return count;
}

static u8 OpponentFixedRow(u8 fixedRow)
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

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!OpponentFixedRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FindFirstDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    if (!OpponentFixedRow(row))
      continue;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidDestroyTarget(row, col))
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

static void BeginHarpiesPetBabyDragonTargeting(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.state = DUEL_CURSOR_HARPIES_PET_BABY_DRAGON_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gMonEffect.row, targetRow);
}

static void ResolveHarpiesPetBabyDragonEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return;

  DestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateHARPIES_PET_BABY_DRAGON(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != HARPIES_PET_BABY_DRAGON)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CountOtherHarpieOnRow(gMonEffect.row, HARPIES_PET_BABY_DRAGON) < 3)
    return FALSE;

  return FindFirstDestroyTarget(&unusedRow, &unusedCol);
}

void ActivateHARPIES_PET_BABY_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(HARPIES_PET_BABY_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginHarpiesPetBabyDragonTargeting();
    return;
  }

  ResolveHarpiesPetBabyDragonEffectForAi();
}

void TrySelectHarpiesPetBabyDragonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidDestroyTarget(targetRow, targetCol)) {
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

void CancelHarpiesPetBabyDragonTargeting(void)
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
