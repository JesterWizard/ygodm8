#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define PAINFUL_CHOICE_SELECT_COUNT 5

void UpdateDuelGfxExceptField(void);

static const u8 sPainfulChoicePickLabels[] APPEND_RODATA = {
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

static u8 CountUndrawnDeckCards(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return deckSize - top;
}

u8 CanActivatePAINFUL_CHOICE(void)
{
  if (CountUndrawnDeckCards(ACTIVE_DUELIST) < PAINFUL_CHOICE_SELECT_COUNT)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static u8 LoadDeckMenuExcluding(u8 turnDuelist, const u8 *exclude, u8 excludeCount,
                                u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;
  u8 e;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u8 skip = FALSE;

    for (e = 0; e < excludeCount; e++) {
      if (exclude[e] == i) {
        skip = TRUE;
        break;
      }
    }
    if (skip)
      continue;

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

static u8 PickDeckIndexExcluding(u8 turnDuelist, const u8 *exclude, u8 excludeCount)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadDeckMenuExcluding(turnDuelist, exclude, excludeCount, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sPainfulChoicePickLabels,
                                         ARRAY_COUNT(sPainfulChoicePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static u8 TakeDeckCardAtIndex(u8 turnDuelist, u8 deckIndex, u16 *outId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  *outId = cardId;
  return TRUE;
}

static u8 SelectFiveFromDeck(u8 turnDuelist, u16 *outIds)
{
  u8 selected = 0;
  u8 i;

  for (i = 0; i < PAINFUL_CHOICE_SELECT_COUNT; i++) {
    u8 deckIndex;
    u16 cardId;

    if (CountUndrawnDeckCards(turnDuelist) == 0)
      break;

    deckIndex = PickDeckIndexExcluding(turnDuelist, NULL, 0);
    if (deckIndex == 0xFF) {
      while (selected < PAINFUL_CHOICE_SELECT_COUNT
             && CountUndrawnDeckCards(turnDuelist) > 0) {
        u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
        u8 autoIndex = gDuelDecks[fixedDuelist].cardsDrawn;

        if (!TakeDeckCardAtIndex(turnDuelist, autoIndex, &cardId))
          break;
        outIds[selected++] = cardId;
      }
      break;
    }

    if (!TakeDeckCardAtIndex(turnDuelist, deckIndex, &cardId))
      break;

    outIds[selected++] = cardId;
  }

  return selected;
}

static u8 LoadRevealedMenu(const u16 *ids, u8 count)
{
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < count; i++)
    gDeckMenu.cards[i] = ids[i];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
  return count;
}

/* Opponent (or AI) picks which of the 5 goes to hand. */
static u8 OpponentPickAmongRevealed(const u16 *ids, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 chosen;

  if (count == 0)
    return 0xFF;

  /* Active player already chose the 5; inactive side picks among them.
   * When AI is active, the human (inactive) gets the pick UI. */
  if (WhoseTurn() == DUEL_PLAYER || gHideEffectText || count == 1)
    return 0;

  DECKMENU_SAVE();
  LoadRevealedMenu(ids, count);
  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sPainfulChoicePickLabels,
                                         ARRAY_COUNT(sPainfulChoicePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0;
  }

  chosen = (u8)gDeckMenu.currentPos;
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosen;
}

static void AddCardIdToHand(u8 turnDuelist, u16 cardId)
{
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
}

static void DestroyPainfulChoiceSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == PAINFUL_CHOICE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void PAINFUL_CHOICE_ResolveBody(void)
{
  u16 revealed[PAINFUL_CHOICE_SELECT_COUNT];
  u8 selected;
  u8 keepIndex;
  u8 i;

  Duel_ShowEffectText(PAINFUL_CHOICE);

  if (IsDuelOver() == TRUE || !CanActivatePAINFUL_CHOICE())
    return;

  selected = SelectFiveFromDeck(ACTIVE_DUELIST, revealed);
  if (selected == 0) {
    DestroyPainfulChoiceSpellZone();
    return;
  }

  keepIndex = OpponentPickAmongRevealed(revealed, selected);
  if (keepIndex >= selected)
    keepIndex = 0;

  AddCardIdToHand(ACTIVE_DUELIST, revealed[keepIndex]);

  for (i = 0; i < selected; i++) {
    if (i == keepIndex)
      continue;
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, revealed[i]);
  }

  DestroyPainfulChoiceSpellZone();
}

APPEND_TEXT void EffectPAINFUL_CHOICE(void)
{
  if (!CanActivatePAINFUL_CHOICE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(PAINFUL_CHOICE, PAINFUL_CHOICE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
