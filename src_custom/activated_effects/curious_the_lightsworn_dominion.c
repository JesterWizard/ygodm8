#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define CURIOUS_MILL_COUNT 1

static u8 sCuriousInit APPEND_DATA = {0};
static u8 sPendingCuriousController APPEND_DATA = {0xFF};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

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

static u8 AddAnyFromGyToHand(u8 fixedDuelist, u8 turnDuelist)
{
  s8 handZone;
  u16 cardId = CARD_NONE;
  u8 i;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (cardId == CARD_NONE)
      return FALSE;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
      u16 gyId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

      if (gyId == CARD_NONE)
        continue;
      cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i - 1);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      break;
    }
    if (cardId == CARD_NONE)
      return FALSE;
  }

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static void OnCuriousLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != CURIOUS_THE_LIGHTSWORN_DOMINION || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(CURIOUS_THE_LIGHTSWORN_DOMINION))
    return;

  /* Resolve after ClearZone so GY includes cards present post-leave. */
  sPendingCuriousController = ev->controller;
}

static void OnCuriousFieldChange(const struct EffectEvent *ev)
{
  u8 controller;
  u8 turnDuelist;

  (void)ev;
  if (sPendingCuriousController > DUEL_OPPONENT || gHideEffectText)
    return;
  if (EffectOpt_IsUsed(CURIOUS_THE_LIGHTSWORN_DOMINION)) {
    sPendingCuriousController = 0xFF;
    return;
  }

  controller = sPendingCuriousController;
  sPendingCuriousController = 0xFF;
  turnDuelist = TurnDuelistForFixed(controller);
  if (!AddAnyFromGyToHand(controller, turnDuelist))
    return;

  Duel_ShowEffectTextTyped(CURIOUS_THE_LIGHTSWORN_DOMINION, 8);
  EffectOpt_MarkUsed(CURIOUS_THE_LIGHTSWORN_DOMINION);
  UpdateDuelGfxExceptField();
}

void CuriousTheLightswornDominion_EnsureInit(void)
{
  if (sCuriousInit)
    return;

  sCuriousInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnCuriousLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnCuriousLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnCuriousLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_FIELD_CHANGE, OnCuriousFieldChange);
}

unsigned char CanActivateCURIOUS_THE_LIGHTSWORN_DOMINION(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != CURIOUS_THE_LIGHTSWORN_DOMINION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CURIOUS_THE_LIGHTSWORN_DOMINION)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return gDuelDecks[fixedDuelist].cardsDrawn + CURIOUS_MILL_COUNT
      <= NumCardsInDeck(fixedDuelist);
}

void ActivateCURIOUS_THE_LIGHTSWORN_DOMINIONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CURIOUS_THE_LIGHTSWORN_DOMINION, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, CURIOUS_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
