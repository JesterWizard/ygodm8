#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jowls_of_dark_demise.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 CanTakeControlOfOpponentMonster(void)
{
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) > 0
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < MAX_ZONES_IN_ROW;
}

static u8 IsValidJowlsTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstJowlsTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidJowlsTargetZone(OPPONENT_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void TakeControlOfMonsterZone(struct DuelCard *src)
{
  u8 destCol;
  struct DuelCard *dst;

  if (src == NULL || src->id == CARD_NONE || !CanTakeControlOfOpponentMonster())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  dst = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][destCol];

  dst->id = src->id;
  dst->isFaceUp = TRUE;
  dst->isLocked = FALSE;
  dst->isDefending = FALSE;
  dst->unkTwo = TRUE; // ponytail: Jowls direct-attack flag; cleared when zone resets
  dst->unk4 = 2;
  SetPermStage(dst, PermStage(src));
  ResetTempStage(dst);
  dst->willChangeSides = TRUE;
  ClearZone(src);
}

static void TakeControlFromOpponentFixedCol(u8 fixedCol)
{
  TakeControlOfMonsterZone(gFixedZones[OPPONENT_MONSTER_ROW][fixedCol]);
}

u8 CanJowlsControlledMonsterAttackDirectly(const struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE && zone->willChangeSides && zone->unkTwo;
}

static void ResolveJowlsEffectForAi(void)
{
  u8 sourceCol = HighestAtkMonInRowExceptGodCards(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);

  if (sourceCol >= MAX_ZONES_IN_ROW)
    return;

  TakeControlOfMonsterZone(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][sourceCol]);
}

static void BeginJowlsTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstJowlsTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(JOWLS_OF_DARK_DEMISE, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET;
  gDuelCursor.currentY = OPPONENT_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, OPPONENT_MONSTER_ROW);
}

void TrySelectJowlsOfDarkDemiseTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidJowlsTargetZone(targetRow, targetCol) || !CanTakeControlOfOpponentMonster()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  TakeControlFromOpponentFixedCol(targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

void CancelJowlsOfDarkDemiseTargeting(void)
{
  PlayMusic(SFX_FORBIDDEN);
  WaitForVBlank();
}

unsigned char CanActivateJowlsOfDarkDemise(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != JOWLS_OF_DARK_DEMISE)
    return FALSE;

  if (gMonEffect.row != OPPONENT_MONSTER_ROW && gMonEffect.row != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanTakeControlOfOpponentMonster();
}

void ActivateJowlsOfDarkDemiseEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginJowlsTargeting(gMonEffect.row, gMonEffect.zone);
    return;
  }

  Duel_ShowEffectTextTyped(JOWLS_OF_DARK_DEMISE, 2);

  if (IsDuelOver() == TRUE)
    return;

  ResolveJowlsEffectForAi();
}
