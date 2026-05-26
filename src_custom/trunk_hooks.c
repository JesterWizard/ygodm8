#include "global.h"
#include "configs/runtime.h"
#include "generated/card_trunk_generated.inc"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];
extern unsigned char gTotalCardQty[];
extern void SortCardsAccordingToContext(void);
extern u8 gUnk_8DFA6A8[];
extern struct CardSortContext gCardSortContext;
extern struct TrunkMenu gTrunkMenu;
extern struct UnkStruct_2021AB4 gUnk2021AB4;
unsigned char GetDeckCardQty(unsigned short);
void SetCardInfo(unsigned short id);
void TrunkMenuDefaultSort(void);
void ApplyNewSortMode(unsigned char);
unsigned short GetNthCardOnScreen(unsigned char);
void sub_800907C(void);
void GoUpOnePosition(void);
void GoDownOnePosition(void);
void GoUpFiftyPositions(void);
void GoDownFiftyPositions(void);
void InitTrunkData(void);
void TryRemoveSelectedCardFromDeck(void);
unsigned char GetTrunkCardQty(unsigned short);
unsigned char GetTrunkCardQuantity(unsigned short);
void InitTrunkCards(void);
void ToggleTrunkDisplayMode(void);
void ToggleSortMode(void);
void QuitTrunkMenu(void);
void RunTrunkTask(unsigned char);
u8 sub_801F098(u16);
unsigned GetDuelistLevel(void);
u8 GetPlayerDeckSize(void);
void AddCardToDeck(unsigned short);
u8 TryRemoveCardFromDeck(u16);
void SetCardInfo(unsigned short id);
extern struct CardInfo gCardInfo;
extern unsigned short gPressedButtons;
void WaitForVBlank(void);

static u16 GetTrunkCardCount(void) {
  return NUM_TRUE_CARDS + (gRuntimeConfig.enable_custom_cards_past_800 == TRUE ? NUM_CUSTOM_TRUNK_CARDS : 0);
}

static u16 GetLastTrackedCardId(void) {
  return CUSTOM_CARD_START + (gRuntimeConfig.enable_custom_cards_past_800 == TRUE ? NUM_CUSTOM_TRUNK_CARDS : 0);
}

static void AppendCustomTrunkCard(void) {
  if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE)
    return;

#if NUM_CUSTOM_TRUNK_CARDS > 0
  {
    u16 i;

    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gTrunkMenu.cards[NUM_TRUE_CARDS + i] = gCustomTrunkCards[i];
  }
#endif
}

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

void SyncCustomTrunkCardQtyMirror(u16 cardId) {
  if (cardId >= CUSTOM_CARD_START && cardId < CUSTOM_CARD_START + NUM_CUSTOM_CARDS)
    gCustomTrunkCardQty[cardId - CUSTOM_CARD_START] = gTrunkCardQty[cardId];
}

void SyncCardOwnershipQty(u16 cardId) {
  gTotalCardQty[cardId] = gTrunkCardQty[cardId] + GetDeckCardQty(cardId);
  SyncCustomTrunkCardQtyMirror(cardId);
}

void SyncTrunkQtyFromOwnedTotal(u16 cardId) {
  u8 deckQty = GetDeckCardQty(cardId);

  if (gTotalCardQty[cardId] >= deckQty)
    gTrunkCardQty[cardId] = gTotalCardQty[cardId] - deckQty;
  else
    gTrunkCardQty[cardId] = 0;

  SyncCustomTrunkCardQtyMirror(cardId);
}

static u8 GetAvailableTrunkQty(u16 cardId) {
  u8 deckQty = GetDeckCardQty(cardId);
  u8 totalQty = gTotalCardQty[cardId];

  if (totalQty == 0 && gTrunkCardQty[cardId] != 0)
    return gTrunkCardQty[cardId];
  if (totalQty < deckQty)
    return 0;
  return totalQty - deckQty;
}

LYN_REPLACE_CHECK(GetTrunkCardQty);
unsigned char GetTrunkCardQty__Replacement(unsigned short cardId) {
  return GetAvailableTrunkQty(cardId);
}

LYN_REPLACE_CHECK(GetTrunkCardQuantity);
unsigned char GetTrunkCardQuantity__Replacement(unsigned short cardId) {
  return GetAvailableTrunkQty(cardId);
}

static void WrapTrunkCursorToList(void) {
  if (gTrunkMenu.currentPos >= GetTrunkCardCount())
    gTrunkMenu.currentPos -= GetTrunkCardCount();
}

static void AddSelectedCardToDeck(void) {
  u16 cardId = GetNthCardOnScreen(2);
  u8 limit = GetRuntimeDeckLimit();

  if (!GetAvailableTrunkQty(cardId)
      || GetPlayerDeckSize() >= limit
      || sub_801F098(cardId) != TRUE) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_RIGHT)
      WaitForVBlank();
    return;
  }

  SetCardInfo(cardId);
  if (GetDuelistLevel() < gCardInfo.cost) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_RIGHT)
      WaitForVBlank();
    return;
  }

  AddCardToDeck(cardId);
  SyncTrunkQtyFromOwnedTotal(cardId);
  SyncCardOwnershipQty(cardId);
  PlayMusic(SFX_SELECT);
}

static void RemoveSelectedCardFromDeck(void) {
  u16 cardId = GetNthCardOnScreen(2);

  if (GetDeckCardQty(cardId) == 0 || TryRemoveCardFromDeck(cardId) != TRUE) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_LEFT)
      WaitForVBlank();
    return;
  }

  SyncTrunkQtyFromOwnedTotal(cardId);
  SyncCardOwnershipQty(cardId);
  PlayMusic(SFX_SELECT);
}

LYN_REPLACE_CHECK(RunTrunkTask);
void RunTrunkTask__Replacement(unsigned char task) {
  switch (task) {
    case 0:
      InitTrunkCards();
      break;
    case 1:
      InitTrunkData();
      break;
    case 2:
      GoDownOnePosition();
      break;
    case 3:
      GoUpOnePosition();
      break;
    case 4:
      GoDownFiftyPositions();
      break;
    case 5:
      GoUpFiftyPositions();
      break;
    case 6:
      ToggleTrunkDisplayMode();
      break;
    case 7:
      AddSelectedCardToDeck();
      break;
    case 8:
      RemoveSelectedCardFromDeck();
      break;
    case 9:
      QuitTrunkMenu();
      break;
    case 10:
      ToggleSortMode();
      break;
  }
}

LYN_REPLACE_CHECK(InitTrunkCards);
void InitTrunkCards__Replacement(void) {
  u32 id;

  for (id = 0; id < GetLastTrackedCardId(); id++) {
    if (id >= CUSTOM_CARD_START) {
      gTrunkCardQty[id] = gRuntimeConfig.start_with_three_copies_of_every_card == TRUE ? 3 : 1;
    }
    else if (gRuntimeConfig.start_with_three_copies_of_every_card == TRUE)
      gTrunkCardQty[id] = 3;
    else
      gTrunkCardQty[id] = gStarterTrunk[id];
  }

  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE) {
    u16 i;

    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gCustomTrunkCardQty[i] = gTrunkCardQty[CUSTOM_CARD_START + i];
  }
}

LYN_REPLACE_CHECK(InitTrunkData);
void InitTrunkData__Replacement(void) {
  unsigned short cardId;

  gTrunkMenu.currentPos = 0;
  gTrunkMenu.displayMode = 1;
  gTrunkMenu.sortMode = CARD_SORT_NUMBER;

  for (cardId = 0; cardId < GetLastTrackedCardId(); cardId++)
    gTotalCardQty[cardId] = gTrunkCardQty[cardId] + GetDeckCardQty(cardId);

  for (cardId = 0; cardId < NUM_TRUE_CARDS; cardId++)
    gTrunkMenu.cards[cardId] = cardId + 1;

  AppendCustomTrunkCard();
}

LYN_REPLACE_CHECK(TrunkMenuDefaultSort);
void TrunkMenuDefaultSort__Replacement(void) {
  gCardSortContext.cards = gTrunkMenu.cards;
  gCardSortContext.cardCount = gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE ? GetTrunkCardCount() : NUM_TRUE_CARDS;
  gCardSortContext.sortMode = gUnk_8DFA6A8[gTrunkMenu.sortMode];
  SortCardsAccordingToContext();
  if (gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == FALSE)
    AppendCustomTrunkCard();
}

LYN_REPLACE_CHECK(ApplyNewSortMode);
void ApplyNewSortMode__Replacement(unsigned char val) {
  gCardSortContext.cards = gTrunkMenu.cards;
  gCardSortContext.cardCount = gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE ? GetTrunkCardCount() : NUM_TRUE_CARDS;
  gCardSortContext.sortMode = gUnk_8DFA6A8[val];
  SortCardsAccordingToContext();
  if (gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == FALSE)
    AppendCustomTrunkCard();
  gTrunkMenu.currentPos = 0;
}

LYN_REPLACE_CHECK(GetNthCardOnScreen);
unsigned short GetNthCardOnScreen__Replacement(u8 n) {
  s16 wrappedIndex = gTrunkMenu.currentPos + n - 2;
  u16 count = GetTrunkCardCount();

  if (wrappedIndex >= count)
    wrappedIndex -= count;
  else if (wrappedIndex < 0)
    wrappedIndex += count;

  return gTrunkMenu.cards[wrappedIndex];
}

LYN_REPLACE_CHECK(sub_800907C);
void sub_800907C__Replacement(void) {
  gUnk2021AB4.currentPos = gTrunkMenu.currentPos;
  gUnk2021AB4.lastValidIndex = GetTrunkCardCount() - 1;
}

LYN_REPLACE_CHECK(GoUpOnePosition);
void GoUpOnePosition__Replacement(void) {
  if (--gTrunkMenu.currentPos < 0)
    gTrunkMenu.currentPos += GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoDownOnePosition);
void GoDownOnePosition__Replacement(void) {
  if (++gTrunkMenu.currentPos > GetTrunkCardCount() - 1)
    gTrunkMenu.currentPos -= GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoUpFiftyPositions);
void GoUpFiftyPositions__Replacement(void) {
  gTrunkMenu.currentPos -= 50;
  if (gTrunkMenu.currentPos < 0)
    gTrunkMenu.currentPos += GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoDownFiftyPositions);
void GoDownFiftyPositions__Replacement(void) {
  gTrunkMenu.currentPos += 50;
  if (gTrunkMenu.currentPos > GetTrunkCardCount() - 1)
    gTrunkMenu.currentPos -= GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

/* LYN_REPLACEMENT(TryAddSelectedCardToDeck) */
void TryAddSelectedCardToDeck__Replacement(void) {
  unsigned isCardRejected = 0;
  unsigned short cardId = GetNthCardOnScreen(2);
  u8 limit = GetRuntimeDeckLimit();

  if (GetAvailableTrunkQty(cardId) && GetPlayerDeckSize() < limit && sub_801F098(cardId) == 1) {
    SetCardInfo(cardId);
    if (GetDuelistLevel() < gCardInfo.cost)
      isCardRejected = 1;
  }
  else
    isCardRejected = 1;

  if (isCardRejected == 1) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_RIGHT)
      WaitForVBlank();
  }
  else {
    gTrunkCardQty[cardId]--;
    AddCardToDeck(cardId);
    SyncTrunkQtyFromOwnedTotal(cardId);
    SyncCardOwnershipQty(cardId);
    PlayMusic(SFX_SELECT);
  }
}

LYN_REPLACE_CHECK(TryRemoveSelectedCardFromDeck);
void TryRemoveSelectedCardFromDeck__Replacement(void) {
  u16 cardId = GetNthCardOnScreen(2);

  if (GetDeckCardQty(cardId) == 0 || TryRemoveCardFromDeck(cardId) != TRUE) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_LEFT)
      WaitForVBlank();
    return;
  }

  if (gTrunkCardQty[cardId] < TRUNK_CARD_LIMIT)
    gTrunkCardQty[cardId]++;
  else
    gTrunkCardQty[cardId] = TRUNK_CARD_LIMIT;

  SyncCardOwnershipQty(cardId);
  PlayMusic(SFX_SELECT);
}
