#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "god_card.h"
#include "harpie_conductor.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sHarpieConductorInit APPEND_DATA = {0};
static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 ControllerHasFaceUpConductor(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == HARPIE_CONDUCTOR)
      return TRUE;
  }

  return FALSE;
}

static u8 IsHarpieMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsLikelySpecialSummonedOpp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidBounceTargetFor(u8 controller, u8 fixedRow, u8 fixedCol)
{
  u8 oppMonsterRow;
  u8 turnDuelist;

  turnDuelist = TurnDuelistForFixed(controller);
  oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                : ACTIVE_DUELIST_MONSTER_ROW;

  if (fixedRow != oppMonsterRow)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST
                                                                   : ACTIVE_DUELIST])
      < 0)
    return FALSE;

  return IsLikelySpecialSummonedOpp(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasBounceTargetFor(u8 controller)
{
  u8 turnDuelist = TurnDuelistForFixed(controller);
  u8 oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                   : ACTIVE_DUELIST_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidBounceTargetFor(controller, oppMonsterRow, col))
      return TRUE;
  }

  return FALSE;
}

static void TryBounceOppOnHarpieReturn(u8 controller)
{
  u8 turnDuelist = TurnDuelistForFixed(controller);
  u8 oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                   : ACTIVE_DUELIST_MONSTER_ROW;
  u8 col;

  if (EffectOpt_IsUsed(HARPIE_CONDUCTOR))
    return;

  if (!ControllerHasFaceUpConductor(controller))
    return;

  if (!FieldHasBounceTargetFor(controller))
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!IsValidBounceTargetFor(controller, oppMonsterRow, col))
      continue;

    zone = gFixedZones[oppMonsterRow][col];
    Duel_ShowEffectTextTyped(HARPIE_CONDUCTOR, 8);
    if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
      return;

    EffectOpt_MarkUsed(HARPIE_CONDUCTOR);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }
}

/* Printed remainder omitted by this ruleset. */
static void OnOtherHarpieLeaveWhileConductor(const struct EffectEvent *ev)
{
  if (ev == NULL || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (ev->cardId == HARPIE_CONDUCTOR || !IsHarpieMonsterId(ev->cardId))
    return;

  TryBounceOppOnHarpieReturn(ev->controller);
}

void HarpieConductor_EnsureInit(void)
{
  if (sHarpieConductorInit)
    return;

  sHarpieConductorInit = TRUE;
  /* ON_LEAVE covers destroy + battle-destroy (both emit leave). */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnOtherHarpieLeaveWhileConductor);
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) < 0)
    return FALSE;

  return IsLikelySpecialSummonedOpp(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
    return;

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

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateHARPIE_CONDUCTOR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_CONDUCTOR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_CONDUCTOR)
    return FALSE;

  /* Name=Harpie Lady via HarpiePerfumer_TreatsNameAsHarpieLady.
   * Harpie leave → bounce opp SS via HarpieConductor_EnsureInit (leave≈return).
   * OPT bounce below. */
  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateHARPIE_CONDUCTOREffect(void)
{
  Duel_ShowEffectTextTyped(HARPIE_CONDUCTOR, 2);

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
