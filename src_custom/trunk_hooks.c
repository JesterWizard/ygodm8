#include "global.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"
#include "player_decks.h"
#include "generated/card_trunk_generated.inc"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];
extern unsigned char gTotalCardQty[];
extern unsigned char gCustomTotalCardQty[];
extern unsigned char gCustomTrunkCardQty[];
extern void SortCardsAccordingToContext(void);
extern u8 gUnk_8DFA6A8[];
extern struct CardSortContext gCardSortContext;
extern struct TrunkMenu gTrunkMenu;
extern u16 gTrunkMenuCustomCards[];
extern u16 gTrunkMenuSortCards[];
extern u16 gTrunkVisibleCardCount;
extern u16 gTrunkVisibleStandardCount;
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
u8 GetPlayerDeckSize(void);
void AddCardToDeck(unsigned short);
u8 TryRemoveCardFromDeck(u16);
void SetCardInfo(unsigned short id);
extern struct CardInfo gCardInfo;
extern unsigned short gPressedButtons;
void WaitForVBlank(void);
void sub_800A3D8(unsigned char);
void sub_800ABB4(void);

static bool8 TrunkHidesUnownedCards(void) {
  return gRuntimeConfig.hide_unowned_trunk_cards;
}

static u8 GetDeckQtyForOwnershipTotals(u16 cardId);
static void WrapTrunkCursorToList(void);

static bool8 IsCustomCardId(u16 cardId) {
  return cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS;
}

static u8 GetTrunkQtyForCard(u16 cardId) {
  if (IsCustomCardId(cardId))
    return gCustomTrunkCardQty[cardId - CUSTOM_CARD_START];
  if (cardId < CUSTOM_CARD_START)
    return gTrunkCardQty[cardId];
  return 0;
}

#define LAST_VANILLA_TRUNK_QTY_CARD_ID 807

static void SetTrunkQtyForCard(u16 cardId, u8 qty) {
  if (IsCustomCardId(cardId)) {
    gCustomTrunkCardQty[cardId - CUSTOM_CARD_START] = qty;
    if (cardId <= LAST_VANILLA_TRUNK_QTY_CARD_ID)
      gTrunkCardQty[cardId] = qty;
    return;
  }

  if (cardId < CUSTOM_CARD_START)
    gTrunkCardQty[cardId] = qty;
}

static bool8 CardIsVisibleInTrunkList(u16 cardId) {
  if (cardId == CARD_NONE)
    return FALSE;
  /* Match on-screen trunk/deck counts (active deck only), not all-deck totals. */
  return GetTrunkQtyForCard(cardId) + GetDeckCardQty(cardId) >= 1;
}

static void SetTrunkVisibleCounts(u16 standardCount, u16 totalCount) {
  gTrunkVisibleStandardCount = standardCount;
  gTrunkVisibleCardCount = totalCount;
}

static void ClampTrunkCursorToVisibleList(void) {
  u16 count = gTrunkVisibleCardCount;

  if (count == 0) {
    gTrunkMenu.currentPos = 0;
    return;
  }

  if (gTrunkMenu.currentPos >= count)
    gTrunkMenu.currentPos = count - 1;
}

static void RebuildVisibleTrunkCardList(void) {
  u16 write = 0;
  u16 i;

  if (!TrunkHidesUnownedCards())
    return;

  for (i = 0; i < NUM_TRUE_CARDS; i++) {
    u16 cardId = i + 1;

    if (CardIsVisibleInTrunkList(cardId))
      gTrunkMenuSortCards[write++] = cardId;
  }

#if NUM_CUSTOM_TRUNK_CARDS > 0
  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE) {
    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++) {
      u16 cardId = gCustomTrunkCards[i];

      if (CardIsVisibleInTrunkList(cardId))
        gTrunkMenuSortCards[write++] = cardId;
    }
  }
#endif

  for (i = write; i < NUM_TRUE_CARDS + NUM_CUSTOM_TRUNK_CARDS; i++)
    gTrunkMenuSortCards[i] = CARD_NONE;

#if NUM_CUSTOM_TRUNK_CARDS > 0
  for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
    gTrunkMenuCustomCards[i] = CARD_NONE;
#endif

  SetTrunkVisibleCounts(write, write);
  ClampTrunkCursorToVisibleList();
}

static u16 GetFullTrunkCardCount(void) {
  return NUM_TRUE_CARDS + (gRuntimeConfig.enable_custom_cards_past_800 == TRUE ? NUM_CUSTOM_TRUNK_CARDS : 0);
}

static u16 GetTrunkCardCount(void) {
  if (TrunkHidesUnownedCards())
    return gTrunkVisibleCardCount;
  return GetFullTrunkCardCount();
}

static u16 GetTrunkSortCardCount(void) {
  if (TrunkHidesUnownedCards() || gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE)
    return GetTrunkCardCount();
  return NUM_TRUE_CARDS;
}

static u16 GetLastTrackedCardId(void) {
  return CUSTOM_CARD_START + (gRuntimeConfig.enable_custom_cards_past_800 == TRUE ? NUM_CUSTOM_TRUNK_CARDS : 0);
}

static u8 GetDeckQtyForOwnershipTotals(u16 cardId) {
  if (PlayerDecks_IsEnabled() == TRUE)
    return PlayerDecks_GetTotalDeckCardQty(cardId);
  return GetDeckCardQty(cardId);
}

static void IncrementTotalCardQty(u16 cardId) {
  SetTotalCardQtyForCard(cardId, GetTotalCardQtyForCard(cardId) + 1);
}

static void AccumulateDeckCardsIntoTotals(const u16 *cards) {
  u8 i;

  for (i = 0; i < DECK_SIZE; i++) {
    u16 cardId = cards[i];

    if (cardId != CARD_NONE)
      IncrementTotalCardQty(cardId);
  }
}

static void AccumulateAllDeckCardsIntoTotals(void) {
  if (PlayerDecks_IsEnabled() == TRUE) {
    u8 active = PlayerDecks_GetActiveIndex();

    AccumulateDeckCardsIntoTotals(active == 1 ? gDeckMenu.cards : gPlayerDeck1Cards);
    AccumulateDeckCardsIntoTotals(active == 2 ? gDeckMenu.cards : gPlayerDeck2Cards);
    AccumulateDeckCardsIntoTotals(active == 3 ? gDeckMenu.cards : gPlayerDeck3Cards);
  }
  else {
    AccumulateDeckCardsIntoTotals(gDeckMenu.cards);
  }
}

static void RefreshTrunkOwnershipTotals(void) {
  u16 cardId;

  for (cardId = 0; cardId < CUSTOM_CARD_START; cardId++)
    gTotalCardQty[cardId] = gTrunkCardQty[cardId];

  for (cardId = CUSTOM_CARD_START; cardId < GetLastTrackedCardId(); cardId++)
    SetTotalCardQtyForCard(cardId, GetTrunkQtyForCard(cardId));

  AccumulateAllDeckCardsIntoTotals();
}

static void AppendCustomTrunkCard(void) {
  if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE)
    return;

#if NUM_CUSTOM_TRUNK_CARDS > 0
  {
    u16 i;

    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gTrunkMenuCustomCards[i] = gCustomTrunkCards[i];
  }
#endif
}

static void RebuildFullTrunkMenuCardList(void) {
  u16 cardId;

  for (cardId = 0; cardId < NUM_TRUE_CARDS; cardId++)
    gTrunkMenu.cards[cardId] = cardId + 1;

  if (!TrunkHidesUnownedCards())
    AppendCustomTrunkCard();
}

static void BuildTrunkSortCardList(void) {
  u16 i;

  if (TrunkHidesUnownedCards())
    return;

  for (i = 0; i < NUM_TRUE_CARDS; i++)
    gTrunkMenuSortCards[i] = gTrunkMenu.cards[i];

#if NUM_CUSTOM_TRUNK_CARDS > 0
  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE) {
    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gTrunkMenuSortCards[NUM_TRUE_CARDS + i] = gTrunkMenuCustomCards[i];
  }
#endif
}

static void FinalizeVisibleTrunkSortCardList(u16 count) {
  u16 i;

  for (i = count; i < NUM_TRUE_CARDS + NUM_CUSTOM_TRUNK_CARDS; i++)
    gTrunkMenuSortCards[i] = CARD_NONE;

#if NUM_CUSTOM_TRUNK_CARDS > 0
  for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
    gTrunkMenuCustomCards[i] = CARD_NONE;
#endif

  SetTrunkVisibleCounts(count, count);
  ClampTrunkCursorToVisibleList();
}

static void ApplyTrunkSortCardList(void) {
  u16 i;

  if (TrunkHidesUnownedCards()) {
    u16 count = gCardSortContext.cardCount;

    if (count == 0)
      count = gTrunkVisibleCardCount;
    FinalizeVisibleTrunkSortCardList(count);
    return;
  }

  for (i = 0; i < NUM_TRUE_CARDS; i++)
    gTrunkMenu.cards[i] = gTrunkMenuSortCards[i];

#if NUM_CUSTOM_TRUNK_CARDS > 0
  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE) {
    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gTrunkMenuCustomCards[i] = gTrunkMenuSortCards[NUM_TRUE_CARDS + i];
  }
#endif
}

static u16 GetTrunkMenuCardAtIndex(u16 index) {
  if (TrunkHidesUnownedCards()) {
    u16 cardId;

    if (index >= gTrunkVisibleCardCount)
      return CARD_NONE;
    cardId = gTrunkMenuSortCards[index];
    if (!CardIsVisibleInTrunkList(cardId))
      return CARD_NONE;
    return cardId;
  }

  if (index < NUM_TRUE_CARDS)
    return gTrunkMenu.cards[index];
#if NUM_CUSTOM_TRUNK_CARDS > 0
  return gTrunkMenuCustomCards[index - NUM_TRUE_CARDS];
#else
  return CARD_NONE;
#endif
}

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

void SyncCustomTrunkCardQtyMirror(u16 cardId) {
  if (!IsCustomCardId(cardId))
    return;

  if (cardId <= LAST_VANILLA_TRUNK_QTY_CARD_ID)
    gTrunkCardQty[cardId] = gCustomTrunkCardQty[cardId - CUSTOM_CARD_START];
}

void SyncCustomTrunkCardQtyMirrorFromVanilla(u16 cardId) {
  if (!IsCustomCardId(cardId))
    return;

  if (cardId <= LAST_VANILLA_TRUNK_QTY_CARD_ID)
    gCustomTrunkCardQty[cardId - CUSTOM_CARD_START] = gTrunkCardQty[cardId];
}

void SyncAllCustomTrunkCardQtyMirrorsToVanilla(void) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_CARDS; i++)
    SyncCustomTrunkCardQtyMirror(CUSTOM_CARD_START + i);
}

void SyncAllCustomTrunkCardQtyMirrorsFromVanilla(void) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_CARDS; i++)
    SyncCustomTrunkCardQtyMirrorFromVanilla(CUSTOM_CARD_START + i);
}

unsigned char GetTotalCardQtyForCard(u16 cardId) {
  if (cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS)
    return gCustomTotalCardQty[cardId - CUSTOM_CARD_START];
  return gTotalCardQty[cardId];
}

void SetTotalCardQtyForCard(u16 cardId, u8 qty) {
  if (cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS)
    gCustomTotalCardQty[cardId - CUSTOM_CARD_START] = qty;
  else
    gTotalCardQty[cardId] = qty;
}

void SyncCardOwnershipQty(u16 cardId) {
  SetTotalCardQtyForCard(cardId, GetTrunkQtyForCard(cardId) + GetDeckQtyForOwnershipTotals(cardId));
  SyncCustomTrunkCardQtyMirror(cardId);
}

void SyncTrunkQtyFromOwnedTotal(u16 cardId) {
  SyncCustomTrunkCardQtyMirror(cardId);
}

static u8 GetAvailableTrunkQty(u16 cardId) {
  return GetTrunkQtyForCard(cardId);
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

static void RemoveSelectedCardFromDeck(void) {
  u16 cardId = GetNthCardOnScreen(2);

  if (GetDeckCardQty(cardId) == 0 || TryRemoveCardFromDeck(cardId) != TRUE) {
    PlayMusic(SFX_FORBIDDEN);
    while (gPressedButtons & DPAD_LEFT)
      WaitForVBlank();
    return;
  }

  if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
  else
    SetTrunkQtyForCard(cardId, TRUNK_CARD_LIMIT);
  SyncCardOwnershipQty(cardId);
  RebuildVisibleTrunkCardList();
  PlayMusic(SFX_SELECT);
}

void TryAddSelectedCardToDeck__Replacement(void);

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
      TryAddSelectedCardToDeck__Replacement();
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
      SetTrunkQtyForCard((u16)id,
        gRuntimeConfig.start_with_three_copies_of_every_card == TRUE ? 3 : 0);
    }
    else if (gRuntimeConfig.start_with_three_copies_of_every_card == TRUE)
      gTrunkCardQty[id] = 3;
    else
      gTrunkCardQty[id] = gStarterTrunk[id];
  }
}

LYN_REPLACE_CHECK(InitTrunkData);
void InitTrunkData__Replacement(void) {
  gTrunkMenu.currentPos = 0;
  gTrunkMenu.displayMode = 1;
  gTrunkMenu.sortMode = CARD_SORT_NUMBER;

  RefreshTrunkOwnershipTotals();
  RebuildVisibleTrunkCardList();
  WrapTrunkCursorToList();
}

LYN_REPLACE_CHECK(TrunkMenuDefaultSort);
void TrunkMenuDefaultSort__Replacement(void) {
  RefreshTrunkOwnershipTotals();
  if (TrunkHidesUnownedCards())
    RebuildVisibleTrunkCardList();
  else
    RebuildFullTrunkMenuCardList();
  BuildTrunkSortCardList();
  gCardSortContext.cards = gTrunkMenuSortCards;
  gCardSortContext.cardCount = GetTrunkSortCardCount();
  gCardSortContext.sortMode = gUnk_8DFA6A8[gTrunkMenu.sortMode];
  SortCardsAccordingToContext();
  ApplyTrunkSortCardList();
  gCardSortContext.cardCount = 0;
  if (!TrunkHidesUnownedCards() && gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == FALSE)
    AppendCustomTrunkCard();
  WrapTrunkCursorToList();
}

LYN_REPLACE_CHECK(ApplyNewSortMode);
void ApplyNewSortMode__Replacement(unsigned char val) {
  RefreshTrunkOwnershipTotals();
  if (TrunkHidesUnownedCards())
    RebuildVisibleTrunkCardList();
  else
    RebuildFullTrunkMenuCardList();
  BuildTrunkSortCardList();
  gCardSortContext.cards = gTrunkMenuSortCards;
  gCardSortContext.cardCount = GetTrunkSortCardCount();
  gCardSortContext.sortMode = gUnk_8DFA6A8[val];
  SortCardsAccordingToContext();
  ApplyTrunkSortCardList();
  gCardSortContext.cardCount = 0;
  if (!TrunkHidesUnownedCards() && gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == FALSE)
    AppendCustomTrunkCard();
  gTrunkMenu.currentPos = 0;
  WrapTrunkCursorToList();
}

LYN_REPLACE_CHECK(GetNthCardOnScreen);
unsigned short GetNthCardOnScreen__Replacement(u8 n) {
  s16 wrappedIndex = gTrunkMenu.currentPos + n - 2;
  u16 count = GetTrunkCardCount();
  u16 cardId;

  if (count == 0)
    return CARD_NONE;

  if (wrappedIndex >= count)
    wrappedIndex -= count;
  else if (wrappedIndex < 0)
    wrappedIndex += count;

  return GetTrunkMenuCardAtIndex(wrappedIndex);
}

LYN_REPLACE_CHECK(sub_800907C);
void sub_800907C__Replacement(void) {
  u16 count = GetTrunkCardCount();

  gUnk2021AB4.currentPos = gTrunkMenu.currentPos;
  gUnk2021AB4.lastValidIndex = count > 0 ? count - 1 : 0;
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
    if (CardExceedsCurrentDuelistLevel(cardId))
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
    AddCardToDeck(cardId);
    SyncCardOwnershipQty(cardId);
    RebuildVisibleTrunkCardList();
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

  if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
  else
    SetTrunkQtyForCard(cardId, TRUNK_CARD_LIMIT);

  SyncCardOwnershipQty(cardId);
  RebuildVisibleTrunkCardList();
  PlayMusic(SFX_SELECT);
}

u8 TrunkMenu_GetTrunkQty(u16 cardId) {
  return GetTrunkQtyForCard(cardId);
}

void TrunkMenu_DecrementTrunkQty(u16 cardId) {
  u8 qty = GetTrunkQtyForCard(cardId);

  if (qty > 0)
    SetTrunkQtyForCard(cardId, qty - 1);
}
