#include "global.h"
#include "common-chax.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_gaia.h"
#include "god_card.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static void ApplyGaiaAtkDelta(s16 delta)
{
  s32 atk;

  if (delta == 0)
    return;

  atk = (s32)gCardInfo.atk + (s32)delta;
  if (atk <= 0)
    gCardInfo.atk = 0;
  else
    gCardInfo.atk = Duel_ClampStat((u32)atk);
}

void ApplyElementalHeroGaiaStatMod(const struct DuelCard *zone)
{
  u16 index;
  s16 targetDelta;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  /* gCardInfo.type check avoids SetCardInfo clobber during overlay pass. */
  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return;

  index = GetDuelBoardCellIndex(zone);
  if (index >= MAX_DUEL_BOARD_CELLS)
    return;

  targetDelta = gElementalHeroGaiaTargetAtkDelta[index];
  if (targetDelta != 0)
    ApplyGaiaAtkDelta(targetDelta);

  if (gElementalHeroGaiaBoostAmount > 0
      && index == gElementalHeroGaiaBoostCellIndex
      && zone->id == ELEMENTAL_HERO_GAIA
      && IsCardFaceUp((struct DuelCard *)zone))
    ApplyGaiaAtkDelta((s16)gElementalHeroGaiaBoostAmount);
}

void ElementalHeroGaia_OnZoneCleared(const struct DuelCard *zone)
{
  u16 index;

  if (zone == NULL)
    return;

  index = GetDuelBoardCellIndex(zone);
  if (index >= MAX_DUEL_BOARD_CELLS)
    return;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    gElementalHeroGaiaTargetAtkDelta[index] = 0;

  if (zone->id == ELEMENTAL_HERO_GAIA) {
    gElementalHeroGaiaBoostCellIndex = 0xFFFF;
    gElementalHeroGaiaBoostAmount = 0;
    UpdateDuelGfxExceptField();
  }
}

static u8 FindGaiaFixedZone(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u8 fixedRow;
    u8 fixedCol;

    if (zone->id != ELEMENTAL_HERO_GAIA)
      continue;

    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
      continue;

    *outRow = fixedRow;
    *outCol = fixedCol;
    return TRUE;
  }

  return FALSE;
}

static u8 ZoneIsValidGaiaTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!IsCardFaceUp(zone))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return Duel_GetZoneFinalAtk(zone) > 0;
}

static u8 FindFirstGaiaTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsValidGaiaTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    *outRow = OPPONENT_MONSTER_ROW;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ApplyGaiaHalveBoost(u8 targetRow, u8 targetCol)
{
  struct DuelCard *targetZone = gFixedZones[targetRow][targetCol];
  struct DuelCard *gaiaZone;
  u8 gaiaRow;
  u8 gaiaCol;
  u16 halfAtk;

  if (!ZoneIsValidGaiaTarget(targetRow, targetCol))
    return;

  if (!FindGaiaFixedZone(&gaiaRow, &gaiaCol))
    return;

  gaiaZone = gFixedZones[gaiaRow][gaiaCol];
  if (gaiaZone == NULL || gaiaZone->id != ELEMENTAL_HERO_GAIA)
    return;

  halfAtk = Duel_GetZoneFinalAtk(targetZone) / 2;
  if (halfAtk == 0)
    return;

  {
    u16 targetIndex = GetDuelBoardCellIndex(targetZone);
    u16 gaiaIndex = GetDuelBoardCellIndex(gaiaZone);

    if (targetIndex >= MAX_DUEL_BOARD_CELLS || gaiaIndex >= MAX_DUEL_BOARD_CELLS)
      return;

    gElementalHeroGaiaTargetAtkDelta[targetIndex] = -(s16)halfAtk;
    gElementalHeroGaiaBoostCellIndex = gaiaIndex;
    gElementalHeroGaiaBoostAmount = halfAtk;
  }

  Duel_RefreshMonsterStatOverlays();
}

static void FinishGaiaTargeting(void)
{
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void BeginGaiaTargeting(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstGaiaTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;
  gDuelCursor.state = DUEL_CURSOR_ELEMENTAL_HERO_GAIA_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originRow, targetRow);
}

static void ResolveGaiaEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstGaiaTarget(&targetRow, &targetCol))
    return;

  ApplyGaiaHalveBoost(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void TrySelectElementalHeroGaiaTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!ZoneIsValidGaiaTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ApplyGaiaHalveBoost(targetRow, targetCol);
  FinishGaiaTargeting();
}

void CancelElementalHeroGaiaTargeting(void)
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

void ElementalHeroGaia_OnFusionSummoned(void)
{
  u8 gaiaRow;
  u8 gaiaCol;
  u8 targetRow;
  u8 targetCol;

  Duel_ShowEffectText(ELEMENTAL_HERO_GAIA);

  if (IsDuelOver() == TRUE)
    return;

  if (!FindGaiaFixedZone(&gaiaRow, &gaiaCol))
    return;

  if (!FindFirstGaiaTarget(&targetRow, &targetCol))
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    BeginGaiaTargeting(gaiaRow, gaiaCol);
  else
    ResolveGaiaEffectForAi();
}
