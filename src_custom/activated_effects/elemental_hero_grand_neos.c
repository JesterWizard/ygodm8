#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsValidOppMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOppMonsterTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppMonsterTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidOppMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, TRUE) != DUEL_ACTION_OK)
    return;

  NotifyDynamicEquipFieldChanged();

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
  u8 col;

  *outRow = OPPONENT_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppMonsterTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateELEMENTAL_HERO_GRAND_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_GRAND_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_GRAND_NEOS)
    return FALSE;

  /* EP Extra return via TryReturnContactFusionsAtEndPhase. OPT bounce 1 opponent monster
   * to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonsterTarget()
      && NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateELEMENTAL_HERO_GRAND_NEOSEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_GRAND_NEOS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidOppMonsterTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
