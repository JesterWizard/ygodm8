#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define CONVERT_CONTACT_DRAW_COUNT 2

void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianArchetypeName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sConvertContactPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianArchetypeName);
}

static u8 ControlsNoMonsters(void)
{
  return Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) == 0;
}

static u8 HandHasNeoSpacian(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsNeoSpacianMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstNeoSpacianDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsNeoSpacianMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

u8 CanActivateCONVERT_CONTACT(void)
{
  if (!ControlsNoMonsters())
    return FALSE;

  if (!HandHasNeoSpacian(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  return FindFirstNeoSpacianDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 LoadNeoSpacianDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsNeoSpacianMonster(cardId))
      continue;

    deckIndexOut[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u8 SendDeckCardAtIndexToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsNeoSpacianMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static u8 PickNeoSpacianDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadNeoSpacianDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sConvertContactPickLabels, ARRAY_COUNT(sConvertContactPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static void CONVERT_CONTACT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 deckIndex;

  Duel_ShowEffectText(CONVERT_CONTACT);

  if (IsDuelOver() == TRUE || !CanActivateCONVERT_CONTACT())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsNeoSpacianMonster, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (FindFirstNeoSpacianDeckIndex(ACTIVE_DUELIST) < 0) {
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  deckIndex = PickNeoSpacianDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF) {
    /* ponytail: cancel on deck pick auto-sends first Neo-Spacian (activation committed). */
    s16 autoIndex = FindFirstNeoSpacianDeckIndex(ACTIVE_DUELIST);

    if (autoIndex >= 0)
      SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, (u8)autoIndex);
  } else {
    SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex);
  }

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, CONVERT_CONTACT_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectCONVERT_CONTACT(void)
{
  if (!CanActivateCONVERT_CONTACT()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CONVERT_CONTACT, CONVERT_CONTACT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
