#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define SNAKE_RAIN_SEND_COUNT 4

void UpdateDuelGfxExceptField(void);

static const u8 sSnakeRainPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 CountReptilesInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 count = 0;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsReptileMonster(gDuelDecks[fixedDuelist].cards[i]))
      count++;
  }

  return count;
}

u8 CanActivateSNAKE_RAIN(void)
{
  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return CountReptilesInDeck(ACTIVE_DUELIST) >= SNAKE_RAIN_SEND_COUNT;
}

static s16 FindFirstReptileDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsReptileMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 LoadReptileDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsReptileMonster(cardId))
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
  if (!IsReptileMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static u8 PickReptileDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadReptileDeckMenu(turnDuelist, deckIndexMap);
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
          sSnakeRainPickLabels, ARRAY_COUNT(sSnakeRainPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static void SendFourReptilesFromDeck(void)
{
  u8 i;

  for (i = 0; i < SNAKE_RAIN_SEND_COUNT; i++) {
    u8 deckIndex;

    if (FindFirstReptileDeckIndex(ACTIVE_DUELIST) < 0)
      break;

    deckIndex = PickReptileDeckIndex(ACTIVE_DUELIST);
    if (deckIndex == 0xFF) {
      while (i < SNAKE_RAIN_SEND_COUNT) {
        s16 autoIndex = FindFirstReptileDeckIndex(ACTIVE_DUELIST);

        if (autoIndex < 0)
          break;
        if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, (u8)autoIndex))
          break;
        i++;
      }
      break;
    }

    if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex))
      break;
  }
}

static void SNAKE_RAIN_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(SNAKE_RAIN);

  if (IsDuelOver() == TRUE || !CanActivateSNAKE_RAIN())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  SendFourReptilesFromDeck();
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectSNAKE_RAIN(void)
{
  if (!CanActivateSNAKE_RAIN()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SNAKE_RAIN, SNAKE_RAIN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
