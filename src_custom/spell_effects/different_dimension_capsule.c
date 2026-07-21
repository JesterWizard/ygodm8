#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "different_dimension_capsule.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "removed_from_play.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define DIFFERENT_DIMENSION_CAPSULE_STANDBY_TURNS 2

void UpdateDuelGfxExceptField(void);

/* Banished card id per fixed backrow cell (opp 0-4, player 5-9). */
static u16 sCapsuleBanishedCard[MAX_ZONES_IN_ROW * 2] APPEND_DATA = {0};

static const u8 sCapsulePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u8 CapsuleBackrowCellIndex(struct DuelCard *spellZone, u8 *cellIndex)
{
  u8 fixedRow;
  u8 fixedCol;

  if (spellZone == NULL || cellIndex == NULL)
    return FALSE;

  if (!Duel_FindFixedZone(spellZone, &fixedRow, &fixedCol))
    return FALSE;

  if (fixedRow == OPPONENT_BACKROW)
    *cellIndex = fixedCol;
  else if (fixedRow == PLAYER_BACKROW)
    *cellIndex = MAX_ZONES_IN_ROW + fixedCol;
  else
    return FALSE;

  return TRUE;
}

static void Capsule_StoreBanishedCard(struct DuelCard *spellZone, u16 cardId)
{
  u8 cellIndex;

  if (!CapsuleBackrowCellIndex(spellZone, &cellIndex))
    return;

  sCapsuleBanishedCard[cellIndex] = cardId;
}

static u16 Capsule_LoadBanishedCard(struct DuelCard *spellZone)
{
  u8 cellIndex;

  if (!CapsuleBackrowCellIndex(spellZone, &cellIndex))
    return CARD_NONE;

  return sCapsuleBanishedCard[cellIndex];
}

static void Capsule_ClearBanishedCard(struct DuelCard *spellZone)
{
  u8 cellIndex;

  if (!CapsuleBackrowCellIndex(spellZone, &cellIndex))
    return;

  sCapsuleBanishedCard[cellIndex] = CARD_NONE;
}

static u8 IsActivatedCapsuleZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == DIFFERENT_DIMENSION_CAPSULE && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE;
}

static u8 DeckHasAnyCard(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  return top < deckSize;
}

static u8 LoadAnyDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    deckIndexOut[menuCount] = i;
    gDeckMenu.cards[menuCount] = gDuelDecks[fixedDuelist].cards[i];
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u8 PickAnyDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadAnyDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER || gHideEffectText) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sCapsulePickLabels, ARRAY_COUNT(sCapsulePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static void RemoveBanishedMatching(u8 fixedDuelist, u16 cardId)
{
  RemovedFromPlay_RemoveMatching(fixedDuelist, cardId);
}

static u8 AddBanishedCardToHand(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  RemoveBanishedMatching(fixedDuelist, cardId);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static void ResolveCapsuleAfterStandby(struct DuelCard *spellZone)
{
  u16 cardId;
  u8 graveyardDuelist;

  if (!IsActivatedCapsuleZone(spellZone))
    return;

  cardId = Capsule_LoadBanishedCard(spellZone);
  Capsule_ClearBanishedCard(spellZone);

  graveyardDuelist = ACTIVE_DUELIST;
  Duel_DestroyZone(spellZone, graveyardDuelist, TRUE);

  if (cardId == CARD_NONE)
    return;

  AddBanishedCardToHand(ACTIVE_DUELIST, cardId);
  UpdateDuelGfxExceptField();
}

void TryApplyDifferentDimensionCapsuleStandby(void)
{
  u8 i;
  struct DuelCard *spellZone;

  if (IsDuelOver() == TRUE)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (!IsActivatedCapsuleZone(spellZone))
      continue;

    IncrementPermStage(spellZone);
    if (spellZone->permStage < DIFFERENT_DIMENSION_CAPSULE_STANDBY_TURNS)
      continue;

    ResolveCapsuleAfterStandby(spellZone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void DIFFERENT_DIMENSION_CAPSULE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckIndex;
  u16 cardId;

  if (IsActivatedCapsuleZone(spellZone)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(DIFFERENT_DIMENSION_CAPSULE);

  if (IsDuelOver() == TRUE || !DeckHasAnyCard(ACTIVE_DUELIST))
    return;

  if (!RemovedFromPlay_IsEnabled()) {
    return;
  }

  deckIndex = PickAnyDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF)
    return;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);

  Capsule_StoreBanishedCard(spellZone, cardId);
  Duel_ActivateContinuousZone(spellZone);
  spellZone->permStage = 0;
  spellZone->unk4 = 1;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDIFFERENT_DIMENSION_CAPSULE(void)
{
  if (Duel_TryResolveSpellThroughTraps(DIFFERENT_DIMENSION_CAPSULE,
                                       DIFFERENT_DIMENSION_CAPSULE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DIFFERENT_DIMENSION_CAPSULE_SelfCheck(void)
{
  if (DIFFERENT_DIMENSION_CAPSULE_STANDBY_TURNS != 2)
    while (1)
      ;
}
#endif
