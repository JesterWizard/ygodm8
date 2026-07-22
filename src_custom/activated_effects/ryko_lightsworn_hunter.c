#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

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

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasTarget(void)
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

static void FinishRyko(struct DuelCard *self)
{
  Duel_MillTopDeckCards(ACTIVE_DUELIST, 3, TRUE);
  if (self != NULL)
    MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (IsValidTarget(fixedRow, fixedCol) && zone != NULL)
    Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE);

  FinishRyko(self);
}

static void CancelTargeting(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  /* Optional destroy — cancel still mills. */
  PlayMusic(SFX_CANCEL);
  FinishRyko(self);
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

unsigned char CanActivateRYKO_LIGHTSWORN_HUNTER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != RYKO_LIGHTSWORN_HUNTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RYKO_LIGHTSWORN_HUNTER)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return CanUseMonsterEffect(zone);
}

void ActivateRYKO_LIGHTSWORN_HUNTEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(RYKO_LIGHTSWORN_HUNTER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (FieldHasTarget()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);
    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  FinishRyko(self);
}
