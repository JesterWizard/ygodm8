#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsValidFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *self;

  if (fixedRow < OPPONENT_MONSTER_ROW || fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == self)
    return FALSE;

  return TRUE;
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidFieldTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidFieldTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* Quick Effect destroy→banish stand-in via Duel_BanishZone. */
  if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidFieldTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidFieldTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMASTER_PEACE_THE_TRUE_DRACOSLAYING_KING(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING)
    return FALSE;

  /* Tribute Continuous S/T + unaffected-by-type FALSE.
   * OPT banish 1 other field card (Quick destroy stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateMASTER_PEACE_THE_TRUE_DRACOSLAYING_KINGEffect(void)
{
  Duel_ShowEffectTextTyped(MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidFieldTarget, ResolveBanishTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
