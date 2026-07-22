#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "summon_tribute.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 IsSetCardZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !zone->isFaceUp;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  return IsSetCardZone(fixedRow, fixedCol);
}

static u8 FieldHasSetTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 TurnDuelistOwningFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 sGranmargMarkUsage APPEND_DATA = {FALSE};

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gFixedZones[gDuelCursor.destY][gDuelCursor.destX];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE);
  if (sGranmargMarkUsage && self != NULL)
    MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void RunGranmargDestroyPickZone(u8 originRow, u8 originCol, u8 markUsage)
{
  if (IsDuelOver() == TRUE)
    return;

  sGranmargMarkUsage = markUsage;
  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER && originRow == PLAYER_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char ShouldActivateGranmargTheRockMonarchTribute(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  if (GetPendingTributeSummonCardId() != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->id != GRANMARG_THE_ROCK_MONARCH || zone->unk4 != 0)
    return FALSE;

  return FieldHasSetTarget();
}

void ActivateGranmargTheRockMonarchTribute(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  Duel_ShowEffectTextTyped(GRANMARG_THE_ROCK_MONARCH, 8);

  if (zone != NULL && IsDuelOver() != TRUE)
    zone->unk4 = 1;

  RunGranmargDestroyPickZone(gActiveEffect.turnRow, gActiveEffect.col, FALSE);
}

unsigned char CanActivateGRANMARG_THE_ROCK_MONARCH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  /* Tribute Summon destroy via ActivateGranmargTheRockMonarchTribute.
   * Field OPT destroy Set target once via usage. */
  return CanUseMonsterEffect(zone) && FieldHasSetTarget();
}

void ActivateGRANMARG_THE_ROCK_MONARCHEffect(void)
{
  Duel_ShowEffectTextTyped(GRANMARG_THE_ROCK_MONARCH, 2);
  RunGranmargDestroyPickZone(gMonEffect.row, gMonEffect.zone, TRUE);
}
