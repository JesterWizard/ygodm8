#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cyber_slash_harpie_lady.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sCyberSlashInit APPEND_DATA = {0};
static u8 sPendingController APPEND_DATA = {0xFF};
static u16 sPendingCardId APPEND_DATA = {CARD_NONE};
static u8 sPendingFixedRow APPEND_DATA = {0};
static u8 sPendingCol APPEND_DATA = {0};

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 IsCyberSlashId(u16 cardId)
{
  return cardId == CYBER_SLASH_HARPIE_LADY || cardId == CYBER_SLASH_HARPY_LADY;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 BounceOppZoneToHand(u8 controller, struct DuelCard *zone)
{
  u8 typeGroup;
  u8 oppTurn = TurnDuelistForFixed(controller) == ACTIVE_DUELIST ? INACTIVE_DUELIST
                                                                : ACTIVE_DUELIST;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[oppTurn]) < 0)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP) {
    s8 empty = FirstEmptyZoneInRow(gTurnHands[oppTurn]);
    u16 cardId;

    if (empty < 0)
      return FALSE;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[oppTurn][empty], cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 OwnMonsterFixedRowFor(u8 controller)
{
  return Duel_FixedMonsterRowForDuelist(controller);
}

static u8 OppMonsterFixedRowFor(u8 controller)
{
  return Duel_FixedMonsterRowForDuelist(controller == DUEL_PLAYER ? DUEL_OPPONENT
                                                                : DUEL_PLAYER);
}

static u8 OppBackrowFixedRowFor(u8 controller)
{
  return controller == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsValidTargetFor(u8 controller, u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 turn = TurnDuelistForFixed(controller);
  u8 oppTurn = turn == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (fixedRow == OppMonsterFixedRowFor(controller)
      || fixedRow == OppBackrowFixedRowFor(controller)) {
    if (FirstEmptyZoneInRow(gTurnHands[oppTurn]) < 0)
      return FALSE;
    return TRUE;
  }

  if (fixedRow == OwnMonsterFixedRowFor(controller))
    return IsHarpieMonster(zone->id) && FirstEmptyZoneInRow(gTurnHands[turn]) >= 0;

  return FALSE;
}

static u8 FieldHasTargetFor(u8 controller)
{
  u8 rows[3];
  u8 r;
  u8 col;

  rows[0] = OppMonsterFixedRowFor(controller);
  rows[1] = OppBackrowFixedRowFor(controller);
  rows[2] = OwnMonsterFixedRowFor(controller);

  for (r = 0; r < 3; r++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTargetFor(controller, rows[r], col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 FindFaceUpCyberSlash(u8 controller, u8 *outRow, u8 *outCol, u16 *outId)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !IsCyberSlashId(zone->id))
      continue;
    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;
    if (EffectOpt_IsUsed(zone->id))
      continue;
    if (!FieldHasTargetFor(controller))
      continue;

    *outRow = row;
    *outCol = col;
    *outId = zone->id;
    return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self;
  u8 controller = sPendingController;
  u8 ok = FALSE;

  if (controller > DUEL_OPPONENT)
    return;
  if (!IsValidTargetFor(controller, fixedRow, fixedCol) || zone == NULL)
    return;

  self = gFixedZones[sPendingFixedRow][sPendingCol];
  if (self == NULL || !IsCyberSlashId(self->id))
    return;

  if (fixedRow == OppMonsterFixedRowFor(controller)
      || fixedRow == OppBackrowFixedRowFor(controller))
    ok = BounceOppZoneToHand(controller, zone);
  else
    ok = Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (!ok)
    return;

  EffectOpt_MarkUsed(sPendingCardId);
  MarkMonsterEffectUsed(self);
  sPendingController = 0xFF;
  sPendingCardId = CARD_NONE;
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  sPendingController = 0xFF;
  sPendingCardId = CARD_NONE;
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 controller = sPendingController;
  u8 rows[2];
  u8 r;
  u8 col;

  if (controller > DUEL_OPPONENT)
    return FALSE;

  rows[0] = OppMonsterFixedRowFor(controller);
  rows[1] = OppBackrowFixedRowFor(controller);

  for (r = 0; r < 2; r++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTargetFor(controller, rows[r], col)) {
        *outRow = rows[r];
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTargetFor(controller, OwnMonsterFixedRowFor(controller), col)) {
      *outRow = OwnMonsterFixedRowFor(controller);
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 IsValidTargetBridge(u8 fixedRow, u8 fixedCol)
{
  if (sPendingController > DUEL_OPPONENT)
    return FALSE;
  return IsValidTargetFor(sPendingController, fixedRow, fixedCol);
}

static void ArmPending(u8 controller, u8 fixedRow, u8 col, u16 cardId)
{
  sPendingController = controller;
  sPendingFixedRow = fixedRow;
  sPendingCol = col;
  sPendingCardId = cardId;
}

static void OnCardActivate(const struct EffectEvent *ev)
{
  u8 activator;
  u8 order[2];
  u8 i;
  u8 row;
  u8 col;
  u16 cardId;

  if (ev == NULL || gHideEffectText)
    return;
  if (!(ev->flags & (EFFECT_EVENT_ACTIVATE_SPELL | EFFECT_EVENT_ACTIVATE_TRAP)))
    return;
  if (sPendingController <= DUEL_OPPONENT)
    return;

  activator = ev->controller;
  if (activator > DUEL_OPPONENT)
    activator = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;

  /* Prefer non-activator (counter-style), then activator. */
  order[0] = activator == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  order[1] = activator;

  for (i = 0; i < 2; i++) {
    if (FindFaceUpCyberSlash(order[i], &row, &col, &cardId)) {
      ArmPending(order[i], row, col, cardId);
      return;
    }
  }
}

void TryResolvePendingCyberSlashBounce(void)
{
  if (sPendingController > DUEL_OPPONENT || sPendingCardId == CARD_NONE)
    return;
  if (IsDuelOver() == TRUE) {
    sPendingController = 0xFF;
    sPendingCardId = CARD_NONE;
    return;
  }
  if (!FieldHasTargetFor(sPendingController)) {
    sPendingController = 0xFF;
    sPendingCardId = CARD_NONE;
    return;
  }

  Duel_ShowEffectTextTyped(sPendingCardId, 2);
  gDuelCursor.destY = sPendingFixedRow;
  gDuelCursor.destX = sPendingCol;
  Duel_SetupPickZone(IsValidTargetBridge, ResolveTarget, CancelTargeting, AiPickTarget);

  if (sPendingController == DUEL_PLAYER && WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

void CyberSlashHarpieLady_EnsureInit(void)
{
  if (sCyberSlashInit)
    return;

  sCyberSlashInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_CARD_ACTIVATE, OnCardActivate);
}

unsigned char CanActivateCYBER_SLASH_HARPIE_LADY(void)
{
  /* Quick Effect: only via ON_CARD_ACTIVATE → TryResolvePendingCyberSlashBounce. */
  return FALSE;
}

void ActivateCYBER_SLASH_HARPIE_LADYEffect(void)
{
}

unsigned char CanActivateCYBER_SLASH_HARPY_LADY(void)
{
  return FALSE;
}

void ActivateCYBER_SLASH_HARPY_LADYEffect(void)
{
}
