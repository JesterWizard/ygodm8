#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "amazoness_archer.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsValidTributeZone(u8 fixedRow, u8 fixedCol, u8 excludeCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (fixedCol == excludeCol)
    return FALSE;

  return TRUE;
}

static u8 CountTributeTargets(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeZone(PLAYER_MONSTER_ROW, col, MAX_ZONES_IN_ROW))
      count++;
  }
  return count;
}

static u8 FindFirstTributeTarget(u8 excludeCol, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeZone(PLAYER_MONSTER_ROW, col, excludeCol)) {
      *outCol = col;
      return TRUE;
    }
  }
  return FALSE;
}

static void ApplyArcherDamage(void)
{
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  Duel_ChangeLp(target, -(s32)AMAZONESS_ARCHER_DAMAGE, TRUE);
}

static void SacrificeFixedMonster(u8 fixedRow, u8 fixedCol)
{
  PlayMusic(SFX_TRIBUTE);
  ClearZoneAndSendMonToGraveyard2(gFixedZones[fixedRow][fixedCol], DUEL_PLAYER);
}

static u8 FindAiTributeTargets(u8 *outCol1, u8 *outCol2)
{
  u8 col;
  u8 cols[MAX_ZONES_IN_ROW];
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id != CARD_NONE) {
      cols[count++] = col;
      if (count >= 2)
        break;
    }
  }

  if (count < 2)
    return FALSE;

  *outCol1 = cols[0];
  *outCol2 = cols[1];
  return TRUE;
}

unsigned char CanActivateAmazonessArcher(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_ARCHER)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return CountTributeTargets() >= 2;

  {
    u8 col1, col2;
    return FindAiTributeTargets(&col1, &col2);
  }
}

void BeginAmazonessArcherTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstTributeTarget(MAX_ZONES_IN_ROW, &targetCol))
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_ARCHER, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1;
  gDuelCursor.currentY = PLAYER_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, PLAYER_MONSTER_ROW);
}

void TrySelectAmazonessArcherTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 nextCol;

  if (!IsValidTributeZone(targetRow, targetCol, gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2 ? gSpellEffectData.col1 : MAX_ZONES_IN_ROW)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1) {
    gSpellEffectData.row1 = targetRow;
    gSpellEffectData.col1 = targetCol;

    if (!FindFirstTributeTarget(targetCol, &nextCol)) {
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
      return;
    }

    PlayMusic(SFX_SELECT);
    gDuelCursor.state = DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2;
    gDuelCursor.currentX = nextCol;
    DisplayCardInfoBar();
    sub_8041E70(gMonEffect.row, PLAYER_MONSTER_ROW);
    return;
  }

  SacrificeFixedMonster(gSpellEffectData.row1, gSpellEffectData.col1);
  SacrificeFixedMonster(targetRow, targetCol);
  ApplyArcherDamage();

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

static void ResolveArcherEffectForAi(void)
{
  u8 col1, col2;

  if (!FindAiTributeTargets(&col1, &col2))
    return;

  {
    struct DuelCard *zone1 = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col1];
    struct DuelCard *zone2 = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col2];

    if (Duel_DestroyZone(zone1, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
    if (Duel_DestroyZone(zone2, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
    ApplyArcherDamage();
  }
}

void ActivateAmazonessArcherEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginAmazonessArcherTargeting(gMonEffect.row, gMonEffect.zone);
    return;
  }

  Duel_ShowEffectTextTyped(AMAZONESS_ARCHER, 2);

  if (IsDuelOver() == TRUE)
    return;

  ResolveArcherEffectForAi();
}
