#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "harpies_feather_storm.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";
static u8 sFeatherStormInit APPEND_DATA = {0};

static u8 ControllerHasWindWingedBeast(u8 turnDuelist)
{
  u8 row = Duel_TurnMonsterRowForDuelist(turnDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (!Duel_CardHasMonsterType(zone->id, TYPE_WINGED_BEAST))
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.attribute == ATTRIBUTE_WIND)
      return TRUE;
  }

  return FALSE;
}

static u8 ControllerHasHarpie(u8 turnDuelist)
{
  u8 row = Duel_TurnMonsterRowForDuelist(turnDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sHarpieName))
      return TRUE;
  }

  return FALSE;
}

static void TryAddFeatherDuster(u8 turnDuelist)
{
  u8 fixedDuelist = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
                        ? DUEL_PLAYER
                        : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 empty;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;

  empty = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == HARPIES_FEATHER_DUSTER) {
      cardId = HARPIES_FEATHER_DUSTER;
      deckIndex = i;
      break;
    }
  }

  if (cardId == CARD_NONE && GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == HARPIES_FEATHER_DUSTER) {
        if (GraveyardExpand_RemoveAtFixed(fixedDuelist, i) == HARPIES_FEATHER_DUSTER) {
          gTurnHands[turnDuelist][empty]->id = HARPIES_FEATHER_DUSTER;
          gTurnHands[turnDuelist][empty]->isFaceUp = FALSE;
          gTurnHands[turnDuelist][empty]->isLocked = FALSE;
          ResetPermStage(gTurnHands[turnDuelist][empty]);
          ResetTempStage(gTurnHands[turnDuelist][empty]);
        }
        return;
      }
    }
  }

  if (cardId != CARD_NONE
      && Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) == DUEL_ACTION_OK) {
    gTurnHands[turnDuelist][empty]->id = cardId;
    gTurnHands[turnDuelist][empty]->isFaceUp = FALSE;
    gTurnHands[turnDuelist][empty]->isLocked = FALSE;
    ResetPermStage(gTurnHands[turnDuelist][empty]);
    ResetTempStage(gTurnHands[turnDuelist][empty]);
  }
}

static u8 DestroyedByOpponentCardEffect(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->controller > DUEL_OPPONENT)
    return FALSE;
  if (ev->fixedRow != OPPONENT_BACKROW && ev->fixedRow != PLAYER_BACKROW)
    return FALSE;
  if (!Duel_IsSpellEffectResolving() && !Duel_IsMonsterEffectResolving())
    return FALSE;
  return WhoseTurn() != ev->controller;
}

static void OnFeatherStormDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != HARPIES_FEATHER_STORM || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (!DestroyedByOpponentCardEffect(ev))
    return;
  if (EffectOpt_IsUsed(HARPIES_FEATHER_STORM))
    return;

  {
    u8 turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST]
                             == &gDuel.duelistbattleState[ev->controller]
                         ? ACTIVE_DUELIST
                         : INACTIVE_DUELIST;

    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      return;

    Duel_ShowEffectTextTyped(HARPIES_FEATHER_STORM, 3);
    TryAddFeatherDuster(turnDuelist);
    EffectOpt_MarkUsed(HARPIES_FEATHER_STORM);
    UpdateDuelGfxExceptField();
  }
}

static void ResolveFeatherStormActivate(struct DuelCard *trapZone, u8 trapTurnDuelist)
{
  if (trapZone == NULL)
    return;

  if (ControllerHasWindWingedBeast(trapTurnDuelist)) {
    Duel_ActivateContinuousZone(trapZone);
    trapZone->unk4 = 1; /* monster-effect lock until turn boundary */
  } else {
    Duel_DestroyZone(trapZone, trapTurnDuelist, FALSE);
  }
}

u8 HarpiesFeatherStorm_BlocksMonsterEffects(u8 fixedDuelist)
{
  struct DuelCard *trap;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  /* Blocks the opponent of the Storm controller. */
  trap = Duel_FindBackrowCard(fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER,
                              HARPIES_FEATHER_STORM, TRUE);
  return trap != NULL && trap->unk4 != 0;
}

void HarpiesFeatherStorm_ClearAtTurnBoundary(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 backrow = fixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *trap = gFixedZones[backrow][col];

      if (trap != NULL && trap->id == HARPIES_FEATHER_STORM && trap->isFaceUp
          && trap->unk4 != 0) {
        trap->unk4 = 0;
        Duel_DestroyZone(trap, Duel_TurnDuelistForFixedDuelist(fixed), FALSE);
      }
    }
  }
}

u8 CanActivateHarpiesFeatherStormFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;
  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HARPIES_FEATHER_STORM)
    return FALSE;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) < 0)
    return FALSE;

  return ControllerHasHarpie(ACTIVE_DUELIST);
}

u8 TryActivateHarpiesFeatherStormFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelCard *handSlot;
  s8 backCol;
  struct DuelCard *trapZone;

  if (!CanActivateHarpiesFeatherStormFromHand(handZone))
    return FALSE;

  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  handSlot = SixCardHand_ZoneAtHandRow(handRow, handZone);
  trapZone = gTurnZones[ACTIVE_DUELIST_BACKROW][backCol];

  Duel_ShowEffectTextTyped(HARPIES_FEATHER_STORM, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;

  CopyCard(trapZone, handSlot);
  trapZone->isFaceUp = TRUE;
  trapZone->isLocked = FALSE;
  trapZone->unk4 = 0;
  ClearZone(handSlot);

  ResolveFeatherStormActivate(trapZone, ACTIVE_DUELIST);
  UpdateDuelGfxExceptField();
  return TRUE;
}

void HarpiesFeatherStorm_EnsureInit(void)
{
  if (sFeatherStormInit)
    return;

  sFeatherStormInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnFeatherStormDestroyed);
}

APPEND_TEXT void EffectHARPIES_FEATHER_STORM(void)
{
  struct DuelCard *trapZone =
      gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  HarpiesFeatherStorm_EnsureInit();
  Duel_ShowTrapResponseText(HARPIES_FEATHER_STORM, gTrapEffectData.originCardId);
  ResolveFeatherStormActivate(trapZone, INACTIVE_DUELIST);
  UpdateDuelGfxExceptField();
}
