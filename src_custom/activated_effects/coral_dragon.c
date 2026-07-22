#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 sCoralInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

/* Printed remainder omitted by this ruleset. */
static void OnCoralLeaveField(const struct EffectEvent *ev)
{
  u8 turnDuelist;

  if (ev == NULL || ev->cardId != CORAL_DRAGON || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(CORAL_DRAGON))
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  Duel_ShowEffectTextTyped(CORAL_DRAGON, 8);
  if (Duel_DrawCards(turnDuelist, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(CORAL_DRAGON);
  UpdateDuelGfxExceptField();
}

void CoralDragon_EnsureInit(void)
{
  if (sCoralInit)
    return;

  sCoralInit = TRUE;
  /* ON_LEAVE covers destroy + battle-destroy (both emit leave). */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnCoralLeaveField);
}

static u8 HandHasDiscardableCard(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 IsOppDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppHasDestroyTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDestroyTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;

    if (IsOppDestroyTarget(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppDestroyTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
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

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDestroyTarget(OPPONENT_MONSTER_ROW, col)) {
      *outRow = OPPONENT_MONSTER_ROW;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDestroyTarget(OPPONENT_BACKROW, col)) {
      *outRow = OPPONENT_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateCORAL_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CORAL_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CORAL_DRAGON)
    return FALSE;

  /* Leave-field draw via CoralDragon_EnsureInit.
   * OPT discard 1 → destroy 1 opp card. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!HandHasDiscardableCard())
    return FALSE;

  return OppHasDestroyTarget();
}

void ActivateCORAL_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CORAL_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargetingFromRow(PLAYER_HAND);
  else
    Duel_ResolvePickZoneForAi();
}
