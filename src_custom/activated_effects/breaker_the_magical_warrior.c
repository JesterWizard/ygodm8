#include "global.h"
#include "common-chax.h"
#include "breaker_the_magical_warrior.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsValidBreakerTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstBreakerTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidBreakerTargetZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 GetGraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static struct DuelCard *GetBreakerSourceZone(void)
{
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static u8 BreakerHasSpellCounter(void)
{
  struct DuelCard *zone = GetBreakerSourceZone();

  return BreakerTheMagicalWarrior_ZoneHasSpellCounter(zone);
}

static void RemoveBreakerSpellCounter(void)
{
  BreakerTheMagicalWarrior_ClearZoneSpellCounter(GetBreakerSourceZone());
}

static void DestroyBreakerTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  Duel_DestroyZone(target, GetGraveyardDuelistForFixedRow(fixedRow), TRUE);
  NotifyDynamicEquipFieldChanged();
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveBreakerEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstBreakerTarget(&targetRow, &targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(BREAKER_THE_MAGICAL_WARRIOR, targetRow, targetCol))
    return;

  RemoveBreakerSpellCounter();
  DestroyBreakerTarget(targetRow, targetCol);
}

unsigned char CanActivateBreakerTheMagicalWarrior(void)
{
  u8 row;
  u8 col;

  if (gMonEffect.id != BREAKER_THE_MAGICAL_WARRIOR)
    return FALSE;

  if (!BreakerHasSpellCounter())
    return FALSE;

  return FindFirstBreakerTarget(&row, &col);
}

static void BeginBreakerTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstBreakerTarget(&targetRow, &targetCol))
    return;

  Duel_ShowEffectTextTyped(BREAKER_THE_MAGICAL_WARRIOR, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

void TrySelectBreakerTheMagicalWarriorTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidBreakerTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  RemoveBreakerSpellCounter();
  DestroyBreakerTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

void CancelBreakerTheMagicalWarriorTargeting(void)
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

void ActivateBreakerTheMagicalWarriorEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginBreakerTargeting(gMonEffect.row, gMonEffect.zone);
    return;
  }

  Duel_ShowEffectTextTyped(BREAKER_THE_MAGICAL_WARRIOR, 2);

  if (IsDuelOver() == TRUE)
    return;

  ResolveBreakerEffectForAi();
}
