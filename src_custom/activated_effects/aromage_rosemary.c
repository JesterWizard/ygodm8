#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  return IsFaceUpMonsterTarget(zone);
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ToggleMonsterBattlePosition(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  zone->isDefending = !zone->isDefending;
  zone->isFaceUp = TRUE;
  Duel_NotifyFixedMonsterRowChanged(fixedRow);
  Duel_NotifyMonsterZoneChanged(zone);
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol))
    return;

  ToggleMonsterBattlePosition(fixedRow, fixedCol);

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  Duel_RefreshMonsterStatOverlays();
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

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsValidTarget(row, col))
        continue;

      if (zone->isDefending) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
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

unsigned char CanActivateAROMAGE_ROSEMARY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_ROSEMARY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_ROSEMARY)
    return FALSE;

  /* Ceiling: LP-higher Plant attack → opp monster effects locked + LP-gain
   * gate need permanent/LP hooks. OPT change 1 face-up battle position. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateAROMAGE_ROSEMARYEffect(void)
{
  Duel_ShowEffectTextTyped(AROMAGE_ROSEMARY, 2);

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
