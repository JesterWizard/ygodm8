#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "weapon_change.h"

void UpdateDuelGfxExceptField(void);

#define WEAPON_CHANGE_LP_COST 700
#define WEAPON_CHANGE_BOARD_CELLS 20

static u8 sWeaponChangeSwapCells[WEAPON_CHANGE_BOARD_CELLS] APPEND_DATA = {0};
static u8 sWeaponChangeClearOnEndedFixed APPEND_DATA = {0xFF};

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + WEAPON_CHANGE_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static u8 IsWarriorOrMachine(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR)
      || Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 IsValidWeaponChangeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsWarriorOrMachine(zone->id);
}

static u8 HasWeaponChangeTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidWeaponChangeTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanPayWeaponChangeCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= WEAPON_CHANGE_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= WEAPON_CHANGE_LP_COST;
}

static u8 CanActivateWeaponChangeIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != WEAPON_CHANGE || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!CanPayWeaponChangeCost())
    return FALSE;

  return HasWeaponChangeTarget();
}

void ApplyWeaponChangeAtkDefSwapToCardInfo(const struct DuelCard *zone)
{
  u16 cell;
  u16 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  cell = GetDuelBoardCellIndex(zone);
  if (cell >= WEAPON_CHANGE_BOARD_CELLS || !sWeaponChangeSwapCells[cell])
    return;

  atk = gCardInfo.atk;
  gCardInfo.atk = gCardInfo.def;
  gCardInfo.def = atk;
}

void TryClearWeaponChangeOnOpponentEndPhase(u8 endedFixedDuelist)
{
  u8 i;

  if (sWeaponChangeClearOnEndedFixed == 0xFF)
    return;
  if (endedFixedDuelist != sWeaponChangeClearOnEndedFixed)
    return;

  for (i = 0; i < WEAPON_CHANGE_BOARD_CELLS; i++)
    sWeaponChangeSwapCells[i] = FALSE;
  sWeaponChangeClearOnEndedFixed = 0xFF;
  Duel_RefreshMonsterStatOverlays();
}

static void MarkWeaponChangeSwap(struct DuelCard *zone)
{
  u16 cell;

  if (zone == NULL)
    return;

  cell = GetDuelBoardCellIndex(zone);
  if (cell >= WEAPON_CHANGE_BOARD_CELLS)
    return;

  sWeaponChangeSwapCells[cell] = TRUE;
  /* Until end of opponent's next turn → clear when that opponent's EP finishes. */
  sWeaponChangeClearOnEndedFixed =
      WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
}

static void ApplyAtkDefSwap(struct DuelCard *zone)
{
  MarkWeaponChangeSwap(zone);
  RefreshFieldMonsterStatOverlays();
}

static void CancelWeaponChangeTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  UpdateDuelGfxExceptField();
}

static u8 AiPickWeaponChangeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidWeaponChangeTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveWeaponChangeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target;

  if (!IsValidWeaponChangeTarget(fixedRow, fixedCol))
    return;

  target = gFixedZones[fixedRow][fixedCol];
  ApplyAtkDefSwap(target);

  if (spellZone != NULL)
    spellZone->effectUsedThisTurn = TRUE;
}

static void ResolveWeaponChangeIgnition(struct DuelCard *zone)
{
  if (!CanActivateWeaponChangeIgnition(zone))
    return;

  Duel_ShowEffectText(WEAPON_CHANGE);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -WEAPON_CHANGE_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (!HasWeaponChangeTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    u8 row;
    u8 col;

    if (AiPickWeaponChangeTarget(&row, &col))
      ResolveWeaponChangeTarget(row, col);
    return;
  }

  Duel_SetupPickZone(IsValidWeaponChangeTarget, ResolveWeaponChangeTarget,
                     CancelWeaponChangeTargeting, AiPickWeaponChangeTarget);
  Duel_EnterPickZoneTargeting();
}

void TryApplyWeaponChangeStandby(void)
{
  u8 col;
  struct DuelCard *zone;

  if (IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];
    if (zone == NULL || zone->id != WEAPON_CHANGE || zone->isFaceUp == FALSE)
      continue;

    zone->effectUsedThisTurn = FALSE;
    if (!CanActivateWeaponChangeIgnition(zone))
      continue;

    gSpellEffectData.row1 = ACTIVE_DUELIST_BACKROW;
    gSpellEffectData.col1 = col;
    ResolveWeaponChangeIgnition(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void WEAPON_CHANGE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT; Standby also via TryApply*). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateWeaponChangeIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveWeaponChangeIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(WEAPON_CHANGE);
}

APPEND_TEXT void EffectWEAPON_CHANGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(WEAPON_CHANGE, WEAPON_CHANGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void WEAPON_CHANGE_SelfCheck(void)
{
  if (WEAPON_CHANGE_LP_COST != 700)
    while (1)
      ;
  if (!Duel_CardHasMonsterType(GAIA_THE_FIERCE_KNIGHT, TYPE_WARRIOR))
    while (1)
      ;
  if (!Duel_CardHasMonsterType(CYBER_DRAGON, TYPE_MACHINE))
    while (1)
      ;
}
#endif
