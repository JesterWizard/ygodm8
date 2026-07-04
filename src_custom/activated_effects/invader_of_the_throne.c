#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "invader_of_the_throne.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);
void CopyCard(struct DuelCard *dst, struct DuelCard *src);

static u8 InvaderOpponentRow(u8 selfFixedRow)
{
  if (selfFixedRow == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;
  if (selfFixedRow == OPPONENT_MONSTER_ROW)
    return PLAYER_MONSTER_ROW;
  return 0xFF;
}

static u8 IsSwappableOpponentMonster(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone;

  if (targetRow != InvaderOpponentRow(gMonEffect.row))
    return FALSE;

  zone = gFixedZones[targetRow][targetCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id) || IsImmuneToControlSwitch(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FindFirstSwappableTarget(u8 *outCol)
{
  u8 targetRow = InvaderOpponentRow(gMonEffect.row);
  u8 col;

  if (targetRow == 0xFF)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsSwappableOpponentMonster(targetRow, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void SwapMonsterZones(struct DuelCard *zoneA, struct DuelCard *zoneB)
{
  struct DuelCard temp;

  CopyCard(&temp, zoneA);
  CopyCard(zoneA, zoneB);
  CopyCard(zoneB, &temp);
  zoneA->willChangeSides = FALSE;
  zoneB->willChangeSides = FALSE;
}

static void ResolveInvaderSwap(u8 targetRow, u8 targetCol)
{
  struct DuelCard *selfZone;
  struct DuelCard *targetZone;

  if (!IsSwappableOpponentMonster(targetRow, targetCol))
    return;

  selfZone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  if (selfZone->id != INVADER_OF_THE_THRONE)
    return;

  targetZone = gFixedZones[targetRow][targetCol];
  {
    u16 selfCardId = selfZone->id;
    u16 targetCardId = targetZone->id;
    u8 selfRow = gMonEffect.row;
    u8 targetFixedRow = targetRow;

    SwapMonsterZones(selfZone, targetZone);
    Duel_NotifyMonsterControlSwitched(selfCardId, targetFixedRow);
    if (IsDuelOver() != TRUE)
      Duel_NotifyMonsterControlSwitched(targetCardId, selfRow);
  }
  Duel_NotifyFixedMonsterRowChanged(gMonEffect.row);
  Duel_NotifyFixedMonsterRowChanged(targetRow);
  Duel_RefreshMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

static void ResolveInvaderEffectForAi(void)
{
  u8 targetRow = InvaderOpponentRow(gMonEffect.row);
  s8 targetCol;

  if (targetRow == 0xFF)
    return;

  targetCol = HighestAtkMonInRowExceptGodCards(gFixedZones[targetRow]);
  if (targetCol < 0 || targetCol >= MAX_ZONES_IN_ROW)
    return;

  if (!IsSwappableOpponentMonster(targetRow, (u8)targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(INVADER_OF_THE_THRONE, targetRow, (u8)targetCol))
    return;

  ResolveInvaderSwap(targetRow, (u8)targetCol);
}

static void BeginInvaderTargeting(void)
{
  u8 targetRow = InvaderOpponentRow(gMonEffect.row);
  u8 targetCol;

  if (!FindFirstSwappableTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(INVADER_OF_THE_THRONE, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.state = DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gMonEffect.row, targetRow);
}

void TrySelectInvaderOfTheThroneTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsSwappableOpponentMonster(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveInvaderSwap(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
}

void CancelInvaderOfTheThroneTargeting(void)
{
  PlayMusic(SFX_FORBIDDEN);
  WaitForVBlank();
}

unsigned char CanActivateInvaderOfTheThrone(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != INVADER_OF_THE_THRONE)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  {
    u8 unusedCol;

    return FindFirstSwappableTarget(&unusedCol);
  }
}

void ActivateInvaderOfTheThroneEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginInvaderTargeting();
    return;
  }

  Duel_ShowEffectTextTyped(INVADER_OF_THE_THRONE, 2);

  if (IsDuelOver() == TRUE)
    return;

  ResolveInvaderEffectForAi();
}
