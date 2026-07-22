#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sShaddollDragonInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
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

static u8 IsOppSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OppHasBounceTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
          || IsOppSpellTrapZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 OppHasSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 BounceOpponentCardToHand(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  s8 empty;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (!IsOppSpellTrapZone(fixedRow, fixedCol))
    return FALSE;

  cardId = zone->id;
  ClearZone(zone);
  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  return TRUE;
}

static u8 BounceFirstOpponentCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
          || IsOppSpellTrapZone(row, col)) {
        if (BounceOpponentCardToHand(row, col))
          return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  return IsOppSpellTrapZone(fixedRow, fixedCol);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidDestroyTarget(fixedRow, fixedCol) || zone == NULL)
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

static u8 DestroyFirstOppSpellTrapFor(u8 turnDuelist)
{
  u8 col;
  u8 backRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_BACKROW
                                             : ACTIVE_DUELIST_BACKROW;
  u8 oppTurn = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[backRow][col];
    u8 typeGroup;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    typeGroup = GetTypeGroup(zone->id);
    if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
      continue;

    if (Duel_DestroyZone(zone, oppTurn, FALSE) == DUEL_ACTION_DUEL_OVER)
      return TRUE;
    NotifyDynamicEquipFieldChanged();
    return TRUE;
  }
  return FALSE;
}

static u8 BounceFirstOppCardFor(u8 turnDuelist)
{
  u8 row;
  u8 col;
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                            : ACTIVE_DUELIST_MONSTER_ROW;
  u8 backRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_BACKROW
                                             : ACTIVE_DUELIST_BACKROW;
  u8 oppTurn = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (NumEmptyZonesInRow(gTurnHands[oppTurn]) <= 0)
    return FALSE;

  for (row = 0; row < 2; row++) {
    u8 turnRow = row == 0 ? monRow : backRow;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[turnRow][col];
      u8 typeGroup;

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      typeGroup = GetTypeGroup(zone->id);
      if (typeGroup == TYPE_GROUP_MONSTER) {
        if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK)
          return TRUE;
        continue;
      }
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
    }
  }
  return FALSE;
}

/* GY-sent: destroy S/T; else FLIP bounce stand-in. */
static void OnShaddollDragonLeaveField(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  u8 did;

  if (ev == NULL || ev->cardId != SHADDOLL_DRAGON || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(SHADDOLL_DRAGON))
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  did = DestroyFirstOppSpellTrapFor(turnDuelist);
  if (!did)
    did = BounceFirstOppCardFor(turnDuelist);
  if (!did)
    return;

  Duel_ShowEffectTextTyped(SHADDOLL_DRAGON, 8);
  EffectOpt_MarkUsed(SHADDOLL_DRAGON);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void ShaddollDragon_EnsureInit(void)
{
  if (sShaddollDragonInit)
    return;

  sShaddollDragonInit = TRUE;
  /* ON_LEAVE covers destroy + battle-destroy (both emit leave). */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnShaddollDragonLeaveField);
}

unsigned char CanActivateSHADDOLL_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_DRAGON)
    return FALSE;

  /* Leave-field destroy S/T / bounce via ShaddollDragon_EnsureInit.
   * FLIP bounce/destroy S/T stand-in once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasBounceTarget() || OppHasSpellTrap();
}

void ActivateSHADDOLL_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SHADDOLL_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (OppHasBounceTarget() && NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) > 0) {
    if (BounceFirstOpponentCard()) {
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
    }
    return;
  }

  if (!OppHasSpellTrap())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
