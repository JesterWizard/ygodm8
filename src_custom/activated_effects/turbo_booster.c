#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

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
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidOppMonsterTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
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
    if (IsValidOppMonsterTarget(OPPONENT_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateTURBO_BOOSTER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TURBO_BOOSTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TURBO_BOOSTER)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonsterTarget();
}

void ActivateTURBO_BOOSTEREffect(void)
{
  Duel_ShowEffectTextTyped(TURBO_BOOSTER, 2);

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

u8 CanSpecialSummonTurboBoosterFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != TURBO_BOOSTER)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonTurboBoosterFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonTurboBoosterFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(TURBO_BOOSTER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
