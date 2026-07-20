#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 CountOppFieldCards(void)
{
  u8 count = 0;
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE)
        count++;
    }
  }

  return count;
}

static u8 IsFaceUpNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW
      && fixedRow != PLAYER_BACKROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && IsGodCard(zone->id))
    return FALSE;

  return zone->isFaceUp;
}

static u8 FieldHasFaceUpNegateTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpNegateTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpNegateTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  zone->unk4 |= 0x80;

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

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateELEMENTAL_HERO_NEBULA_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_NEBULA_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_NEBULA_NEOS)
    return FALSE;

  /* ponytail: Extra SS trigger + EP banish field FALSE.
   * Ceiling: OPT draw = opp card count, then mark 1 face-up negated. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpNegateTarget();
}

void ActivateELEMENTAL_HERO_NEBULA_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 drawCount;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_NEBULA_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  drawCount = CountOppFieldCards();
  if (drawCount > 0) {
    if (Duel_DrawCards(ACTIVE_DUELIST, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  if (!FieldHasFaceUpNegateTarget()) {
    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    return;
  }

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpNegateTarget, ResolveNegateTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
