#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "necrovalley_temple.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 sTempleInit APPEND_DATA = {0};

static const u16 sNecrovalleySpellTraps[] APPEND_RODATA = {
  NECROVALLEY,
  IMPERIAL_TOMBS_OF_NECROVALLEY,
  HIDDEN_TEMPLES_OF_NECROVALLEY,
  NECROVALLEY_THRONE,
};

#define NECROVALLEY_TEMPLE_OPP_PENALTY 500

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FieldHasGravekeepers(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp
          && Duel_CardIsMonster(zone->id)
          && Duel_CardNameContains(zone->id, sGravekeepersName))
        return TRUE;
    }
  }

  return FALSE;
}

static void TryActivateNecrovalleyFromHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  s8 empty;

  if (Duel_IsBackrowCardOnField(NECROVALLEY, TRUE))
    return;

  empty = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && gTurnHands[INACTIVE_DUELIST][i]->id == NECROVALLEY) {
      struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];

      slot->id = NECROVALLEY;
      slot->isFaceUp = TRUE;
      slot->isLocked = FALSE;
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      return;
    }
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == NECROVALLEY) {
        struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];

        GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
        slot->id = NECROVALLEY;
        slot->isFaceUp = TRUE;
        slot->isLocked = FALSE;
        return;
      }
    }
  }
}

void ApplyNecrovalleyTempleOppStatPenaltyToCardInfo(const struct DuelCard *zone)
{
  u8 controller;
  u8 templeController;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (!Necrovalley_IsActive() || !FieldHasGravekeepers())
    return;
  if (Duel_FindBackrowCardOnField(NECROVALLEY_TEMPLE, TRUE) == NULL)
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;

  /* Penalty applies to the opponent of whoever controls Temple. */
  if (Duel_FindBackrowCard(DUEL_PLAYER, NECROVALLEY_TEMPLE, TRUE) != NULL)
    templeController = DUEL_PLAYER;
  else if (Duel_FindBackrowCard(DUEL_OPPONENT, NECROVALLEY_TEMPLE, TRUE) != NULL)
    templeController = DUEL_OPPONENT;
  else
    return;

  if (controller == templeController)
    return;

  gCardInfo.atk = Duel_ClampStat(
      (u32)gCardInfo.atk > NECROVALLEY_TEMPLE_OPP_PENALTY
          ? (u32)gCardInfo.atk - NECROVALLEY_TEMPLE_OPP_PENALTY
          : 0);
  gCardInfo.def = Duel_ClampStat(
      (u32)gCardInfo.def > NECROVALLEY_TEMPLE_OPP_PENALTY
          ? (u32)gCardInfo.def - NECROVALLEY_TEMPLE_OPP_PENALTY
          : 0);
}

static void ActivateNECROVALLEY_TEMPLEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, NECROVALLEY_TEMPLE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* Destroy → Set Necrovalley S/T via NecrovalleyTemple_EnsureInit.
   * Place Necrovalley from hand/GY when GK present; continuous −500 via overlay. */
  if (FieldHasGravekeepers())
    TryActivateNecrovalleyFromHandOrGy();

  UpdateDuelGfxExceptField();
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u16 FindNecrovalleySpellTrapInDeck(u8 turnDuelist)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sNecrovalleySpellTraps); i++) {
    if (Duel_FindDeckCardIndex(turnDuelist, sNecrovalleySpellTraps[i]) >= 0)
      return sNecrovalleySpellTraps[i];
  }
  return CARD_NONE;
}

static u8 SetNecrovalleySpellTrapFromDeck(u8 turnDuelist, u16 cardId)
{
  s8 empty;
  s16 deckIndex;
  struct DuelCard *slot;
  u8 backRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_BACKROW
                                             : INACTIVE_DUELIST_BACKROW;

  empty = FirstEmptyZoneInRow(gTurnZones[backRow]);
  if (empty < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);

  slot = gTurnZones[backRow][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

static void OnTempleDestroyed(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  u16 cardId;

  if (ev == NULL || ev->cardId != NECROVALLEY_TEMPLE || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(NECROVALLEY_TEMPLE))
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  cardId = FindNecrovalleySpellTrapInDeck(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(NECROVALLEY_TEMPLE, 8);
  if (!SetNecrovalleySpellTrapFromDeck(turnDuelist, cardId))
    return;

  EffectOpt_MarkUsed(NECROVALLEY_TEMPLE);
  UpdateDuelGfxExceptField();
}

void NecrovalleyTemple_EnsureInit(void)
{
  if (sTempleInit)
    return;

  sTempleInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnTempleDestroyed);
}

void TryActivateNECROVALLEY_TEMPLEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(NECROVALLEY_TEMPLE,
                                         ActivateNECROVALLEY_TEMPLEZone);
}
