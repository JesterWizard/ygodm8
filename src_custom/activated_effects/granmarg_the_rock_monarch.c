#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
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

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE);
  if (self != NULL)
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

unsigned char CanActivateGRANMARG_THE_ROCK_MONARCH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRANMARG_THE_ROCK_MONARCH)
    return FALSE;

  /* ponytail: Tribute Summon trigger. Ceiling: once via usage if Set target. */
  return CanUseMonsterEffect(zone) && FieldHasSetTarget();
}

void ActivateGRANMARG_THE_ROCK_MONARCHEffect(void)
{
  Duel_ShowEffectTextTyped(GRANMARG_THE_ROCK_MONARCH, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
