#include "global.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"
#include "player_decks.h"
#include "gfx_reg_buffers.h"
#include "text.h"
#include "generated/card_trunk_generated.inc"
#include "deck_menu.h"
#include "duel_helpers.h"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];
extern unsigned char gTotalCardQty[];
extern unsigned char gCustomTotalCardQty[];
extern unsigned char gCustomTrunkCardQty[];
extern unsigned char gCustomShopCardQty[];
extern unsigned char gCustomPlayerTempCardQty[];
extern unsigned char gCustomShopTempCardQty[];
extern unsigned char gCustomTrunkCardQtyFlashPrimary[];
extern unsigned char gCustomTrunkCardQtyFlashBackup[];
extern unsigned char gCustomShopCardQtyFlashPrimary[];
extern unsigned char gCustomShopCardQtyFlashBackup[];
extern unsigned char gCustomPlayerTempCardQtyFlashPrimary[];
extern unsigned char gCustomPlayerTempCardQtyFlashBackup[];
int sub_80588C4(u8 *, int, int);
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
void sub_8009364(void);
void sub_800ABD0(void);
void sub_800AA58(unsigned char);
extern u8 gTrunkSubMenuExitRequest;
extern u8 gTrunkExtraDeckViewActive;
u16 GetSelectedCardWithOffset(u8 offset);
unsigned IsPlayerDeckNonempty(void);

/* ========================================================================
 * Extra Deck Helpers
 *
 * Each player deck (1-3) has a 15-card extra deck stored in EWRAM.
 * Fusion cards go here; they are blocked from the main deck.
 * ======================================================================== */

static u16 *GetActiveExtraDeck(void) {
  u8 active = PlayerDecks_IsEnabled() == TRUE
                ? PlayerDecks_GetActiveIndex() : 1;

  switch (active) {
  case 1: return gPlayerDeck1ExtraDeck;
  case 2: return gPlayerDeck2ExtraDeck;
  case 3: return gPlayerDeck3ExtraDeck;
  default: return gPlayerDeck1ExtraDeck;
  }
}

u8 GetExtraDeckSize(void) {
  u16 *extra = GetActiveExtraDeck();
  u8 i, count = 0;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    if (extra[i] != CARD_NONE)
      count++;
  return count;
}

u8 ExtraDeck_GetCardQty(u16 cardId) {
  u16 *extra = GetActiveExtraDeck();
  u8 i, qty = 0;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    if (extra[i] == cardId)
      qty++;
  return qty;
}

static u16 ExtraDeck_GetNthCard(u16 index) {
  u16 *extra = GetActiveExtraDeck();
  u8 i;

  for (i = 0; i < EXTRA_DECK_SIZE; i++) {
    if (extra[i] == CARD_NONE)
      continue;
    if (index == 0)
      return extra[i];
    index--;
  }
  return CARD_NONE;
}

void ExtraDeck_AddCard(u16 cardId) {
  u16 *extra = GetActiveExtraDeck();
  u8 i;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    if (extra[i] == CARD_NONE) {
      extra[i] = cardId;
      return;
    }
}

u8 ExtraDeck_TryRemoveCard(u16 cardId) {
  u16 *extra = GetActiveExtraDeck();
  u8 i;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    if (extra[i] == cardId) {
      extra[i] = CARD_NONE;
      return TRUE;
    }
  return FALSE;
}

static bool8 IsFusionCard(u16 cardId) {
  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;
  return gCardData_NEW[cardId].color == COLOR_FUSION;
}

static bool8 TrunkHidesUnownedCards(void) {
  return gRuntimeConfig.hide_unowned_trunk_cards;
}

static u8 GetDeckQtyForOwnershipTotals(u16 cardId);
static u8 GetExtraDeckQtyForOwnershipTotals(u16 cardId);
static void WrapTrunkCursorToList(void);

static bool8 IsCustomCardId(u16 cardId) {
  return cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS;
}

static u8 GetTrunkQtyForCard(u16 cardId) {
  if (cardId >= NUM_TOTAL_CARDS)
    return 0;
  if (IsCustomCardId(cardId))
    return gCustomTrunkCardQty[cardId - CUSTOM_CARD_START];
  if (cardId < CUSTOM_CARD_START)
    return gTrunkCardQty[cardId];
  return 0;
}

static void WriteCustomCardQtyFlashPaddingAt(int flashBase) {
  u16 i;
  u8 zero = 0;

  for (i = NUM_CUSTOM_CARDS; i < CUSTOM_CARD_QTY_BYTES; i++)
    sub_80588C4(&zero, flashBase + i, 1);
}

void SanitizeCustomCardQtyBuffers(void) {
  u16 i;

  if (NUM_CUSTOM_CARDS >= CUSTOM_CARD_QTY_BYTES)
    return;

  for (i = NUM_CUSTOM_CARDS; i < CUSTOM_CARD_QTY_BYTES; i++) {
    gCustomTrunkCardQty[i] = 0;
    gCustomShopCardQty[i] = 0;
    gCustomPlayerTempCardQty[i] = 0;
    gCustomTotalCardQty[i] = 0;
    gCustomShopTempCardQty[i] = 0;
  }

  WriteCustomCardQtyFlashPaddingAt((int)gCustomTrunkCardQtyFlashPrimary);
  WriteCustomCardQtyFlashPaddingAt((int)gCustomTrunkCardQtyFlashBackup);
  WriteCustomCardQtyFlashPaddingAt((int)gCustomShopCardQtyFlashPrimary);
  WriteCustomCardQtyFlashPaddingAt((int)gCustomShopCardQtyFlashBackup);
  WriteCustomCardQtyFlashPaddingAt((int)gCustomPlayerTempCardQtyFlashPrimary);
  WriteCustomCardQtyFlashPaddingAt((int)gCustomPlayerTempCardQtyFlashBackup);
}

#define LAST_VANILLA_TRUNK_QTY_CARD_ID 807

static void SetTrunkQtyForCard(u16 cardId, u8 qty) {
  if (cardId >= NUM_TOTAL_CARDS)
    return;

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
  /* Match on-screen trunk/main/extra counts (active deck only), not all-deck totals. */
  return GetTrunkQtyForCard(cardId) + GetDeckCardQty(cardId) + ExtraDeck_GetCardQty(cardId) >= 1;
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

u16 GetTrunkCardCount(void) {
  if (gTrunkExtraDeckViewActive)
    return GetExtraDeckSize();
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

static u8 CountCardInExtraDeck(const u16 *extra, u16 cardId) {
  u8 i, qty = 0;

  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    if (extra[i] == cardId)
      qty++;
  return qty;
}

static u8 GetExtraDeckQtyForOwnershipTotals(u16 cardId) {
  if (PlayerDecks_IsEnabled() == TRUE)
    return CountCardInExtraDeck(gPlayerDeck1ExtraDeck, cardId)
      + CountCardInExtraDeck(gPlayerDeck2ExtraDeck, cardId)
      + CountCardInExtraDeck(gPlayerDeck3ExtraDeck, cardId);
  return ExtraDeck_GetCardQty(cardId);
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

static void AccumulateExtraDeckCardsIntoTotals(const u16 *cards) {
  u8 i;

  for (i = 0; i < EXTRA_DECK_SIZE; i++) {
    u16 cardId = cards[i];

    if (cardId != CARD_NONE)
      IncrementTotalCardQty(cardId);
  }
}

static void AccumulateAllExtraDeckCardsIntoTotals(void) {
  if (PlayerDecks_IsEnabled() == TRUE) {
    AccumulateExtraDeckCardsIntoTotals(gPlayerDeck1ExtraDeck);
    AccumulateExtraDeckCardsIntoTotals(gPlayerDeck2ExtraDeck);
    AccumulateExtraDeckCardsIntoTotals(gPlayerDeck3ExtraDeck);
  }
  else {
    AccumulateExtraDeckCardsIntoTotals(gPlayerDeck1ExtraDeck);
  }
}

static void RefreshTrunkOwnershipTotals(void) {
  u16 cardId;

  for (cardId = 0; cardId < CUSTOM_CARD_START; cardId++)
    gTotalCardQty[cardId] = gTrunkCardQty[cardId];

  for (cardId = CUSTOM_CARD_START; cardId < GetLastTrackedCardId(); cardId++)
    SetTotalCardQtyForCard(cardId, GetTrunkQtyForCard(cardId));

  AccumulateAllDeckCardsIntoTotals();
  AccumulateAllExtraDeckCardsIntoTotals();
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
  if (gTrunkExtraDeckViewActive)
    return ExtraDeck_GetNthCard(index);

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
  if (cardId >= NUM_TOTAL_CARDS)
    return 0;
  if (cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS)
    return gCustomTotalCardQty[cardId - CUSTOM_CARD_START];
  return gTotalCardQty[cardId];
}

void SetTotalCardQtyForCard(u16 cardId, u8 qty) {
  if (cardId >= NUM_TOTAL_CARDS)
    return;
  if (cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS)
    gCustomTotalCardQty[cardId - CUSTOM_CARD_START] = qty;
  else
    gTotalCardQty[cardId] = qty;
}

void SyncCardOwnershipQty(u16 cardId) {
  SetTotalCardQtyForCard(cardId, GetTrunkQtyForCard(cardId)
    + GetDeckQtyForOwnershipTotals(cardId)
    + GetExtraDeckQtyForOwnershipTotals(cardId));
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
  u16 count = GetTrunkCardCount();

  if (count == 0) {
    gTrunkMenu.currentPos = 0;
    return;
  }

  if (gTrunkMenu.currentPos >= count)
    gTrunkMenu.currentPos -= count;
}

static void RemoveSelectedCardFromDeck(void) {
  u16 cardId = GetNthCardOnScreen(2);

  /* Try main deck first */
  if (GetDeckCardQty(cardId) > 0 && TryRemoveCardFromDeck(cardId) == TRUE)
    goto return_to_trunk;

  /* Fall back to extra deck */
  if (ExtraDeck_TryRemoveCard(cardId) == TRUE)
    goto return_to_trunk;

  PlayMusic(SFX_FORBIDDEN);
  while (gPressedButtons & DPAD_LEFT)
    WaitForVBlank();
  return;

return_to_trunk:
  if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
  else
    SetTrunkQtyForCard(cardId, TRUNK_CARD_LIMIT);
  SyncCardOwnershipQty(cardId);
  RebuildVisibleTrunkCardList();
  PlayMusic(SFX_SELECT);
}

static bool8 ExtraDeck_ReturnSelectedCardToTrunk(void) {
  u16 cardId = GetNthCardOnScreen(2);

  if (cardId == CARD_NONE || ExtraDeck_TryRemoveCard(cardId) != TRUE)
    return FALSE;

  if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
  else
    SetTrunkQtyForCard(cardId, TRUNK_CARD_LIMIT);

  SyncCardOwnershipQty(cardId);
  RebuildVisibleTrunkCardList();

  if (GetExtraDeckSize() == 0)
    gTrunkExtraDeckViewActive = FALSE;
  WrapTrunkCursorToList();
  return TRUE;
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
      if (gTrunkExtraDeckViewActive) {
        if (ExtraDeck_ReturnSelectedCardToTrunk() == TRUE) {
          PlayMusic(SFX_SELECT);
        } else {
          PlayMusic(SFX_FORBIDDEN);
          while (gPressedButtons & DPAD_LEFT)
            WaitForVBlank();
        }
      } else {
        RemoveSelectedCardFromDeck();
      }
      break;
    case 9:
      if (gTrunkExtraDeckViewActive) {
        gTrunkExtraDeckViewActive = FALSE;
        gTrunkMenu.currentPos = 0;
        TrunkMenuDefaultSort();
        sub_800A3D8(3);
        sub_800ABD0();
        sub_800AA58(6);
      } else {
        QuitTrunkMenu();
      }
      break;
    case 10:
      if (!gTrunkExtraDeckViewActive)
        ToggleSortMode();
      break;
  }
}

LYN_REPLACE_CHECK(InitTrunkCards);
void InitTrunkCards__Replacement(void) {
  u32 id;

  SanitizeCustomCardQtyBuffers();

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
  gTrunkExtraDeckViewActive = FALSE;

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

  /* Extra deck view: don't wrap displayed positions past the list end.
   * The trunk list renderer asks for rows past the list end; without this guard the
   * wrapping logic would loop back and show the first extra deck card
   * again in later slots.  Cursor navigation (GoUp/Down) still wraps
   * because it uses GetTrunkCardCount separately. */
  if (gTrunkExtraDeckViewActive) {
    if (wrappedIndex < 0 || wrappedIndex >= count)
      return CARD_NONE;
    return GetTrunkMenuCardAtIndex(wrappedIndex);
  }

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
  unsigned short cardId = GetNthCardOnScreen(2);

  /* Extra deck view: A-button removes card from extra deck back to trunk */
  if (gTrunkExtraDeckViewActive) {
    if (ExtraDeck_ReturnSelectedCardToTrunk() == TRUE) {
      PlayMusic(SFX_SELECT);
    }
    else {
      PlayMusic(SFX_FORBIDDEN);
      while (gPressedButtons & DPAD_RIGHT)
        WaitForVBlank();
    }
    return;
  }

  /* Normal view: add to main deck (reject fusion cards) */
  {
    unsigned isCardRejected = 0;
    u8 limit = GetRuntimeDeckLimit();

    if (GetAvailableTrunkQty(cardId) && GetPlayerDeckSize() < limit && sub_801F098(cardId) == 1) {
      if (CardExceedsCurrentDuelistLevel(cardId))
        isCardRejected = 1;
      if (IsFusionCard(cardId))
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

void TrunkMenu_IncrementTrunkQty(u16 cardId) {
  if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
  else
    SetTrunkQtyForCard(cardId, TRUNK_CARD_LIMIT);
}

/* ========================================================================
 * Trunk Sub-Menu Extension Framework
 *
 * The vanilla trunk sub-menu has 3 hard-coded options (Details, Move to
 * Deck, Return to Trunk).  This framework lets you register additional
 * options - each with a 20-char label and an action callback - that
 * appear as extra rows in the sub-menu, navigable via DPAD up/down with
 * cursor OAM tracking.
 *
 * How to register an option:
 *   1. Write an action callback:  void MyAction(void) { ... }
 *   2. Define a 20-char label (pad with spaces): "My Option           "
 *   3. At init time, populate gTrunkSubMenuCustomOptions[] and set
 *      gTrunkSubMenuCustomCount.
 *
 * ponytail: labels are English-only for now.  Localization can be added
 *           later by extending the _() macro in the label definition.
 * ======================================================================== */

extern unsigned short gOamBuffer[];
extern unsigned short gUnk_808C240[][30];
extern unsigned char g8DF811C[];
void Trunk_A_Submenu(void);
unsigned short sub_08007FEC(unsigned char, unsigned char, unsigned short);
void sub_800800C(unsigned char, unsigned char, unsigned short, unsigned short);
void sub_800AA58(unsigned char);
void sub_800ABD0(void);
void sub_800ABA8(void);
void sub_8009364(void);
int TrunkSubmenuProcessInput(void);

typedef void (*TrunkSubMenuCallback)(void);

typedef struct {
    const u8 *label;            /* 20-char padded label */
    TrunkSubMenuCallback action;
} TrunkSubMenuOption;

#define TRUNK_SUB_MENU_MAX_CUSTOM   5
#define TRUNK_SUB_MENU_VANILLA_COUNT 3

extern TrunkSubMenuOption gTrunkSubMenuCustomOptions[];
extern u8 gTrunkSubMenuCustomCount;

static u8 TrunkSubMenu_TotalOptionCount(void) {
    return TRUNK_SUB_MENU_VANILLA_COUNT + gTrunkSubMenuCustomCount;
}

/* ---- cursor OAM ---- */

static void TrunkSubMenu_SetCursorOam(void) {
    u32 *oam = (u32 *)&gOamBuffer[6 * 4];
    u8 y = 72 + gTrunkMenu.cursorState * 16;

    oam[0] = y | (56 << 16) | 0x40000000;
    oam[1] = 0xC120;
    oam[2] = y | (56 << 16) | 0x40000800;
    oam[3] = 0x120;
}

static void TrunkSubMenu_ClearCursorOam(void) {
    u32 *oam = (u32 *)&gOamBuffer[6 * 4];

    oam[0] = 0;
    oam[1] = 0;
    oam[2] = 0;
    oam[3] = 0;
}

/* ---- VBlank callback (same as vanilla sub_8008A5C) ---- */

static void TrunkSubMenu_VBlank(void) {
    LoadPalettes();
    LoadOam();
    REG_DISPCNT = DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON |
                  DISPCNT_WIN0_ON | DISPCNT_OBJWIN_ON;
    REG_BLDALPHA = 6;
    REG_BLDY = 10;
    REG_BLDCNT |= 8;
}

/* ---- extended render for custom option rows ---- */

static void TrunkSubMenu_RenderCustomOptions(void) {
    u8 i, k;
    u16 r7;

    if (gTrunkSubMenuCustomCount == 0)
        return;

    r7 = sub_08007FEC(9, 9, 0x7800) & 0xFF00;

    /* Render tilemap entries for all custom option rows.  The vanilla
     * sub_8009364 only writes rows 11-14 (options 0 and 1) and the
     * pre-baked tilemap at rows 15-18 is blank, so custom options
     * start at rows 15-16 (unused 3rd option slot). */
    for (k = 0; k < gTrunkSubMenuCustomCount; k++) {
        u8 optIdx   = TRUNK_SUB_MENU_VANILLA_COUNT + k;
        u8 topRow   = 11 + 2 * optIdx - 2;  /* -2 shifts past blank 3rd vanilla slot */
        u8 botRow   = topRow + 1;
        u16 topOff  = 21 + 40 * optIdx;
        u16 botOff  = 23 + 40 * optIdx;

        for (i = 0; i < 20; i++) {
            sub_800800C(i + 9, topRow, 0x7800,
                        (g8DF811C[i] + topOff) | r7);
            sub_800800C(i + 9, botRow, 0x7800,
                        (g8DF811C[i] + botOff) | r7);
        }
    }

    /* Render custom option text into cbb1 at tile index 141 (= 21 + 3*40).
     * Each option line is 20 chars × 4 tiles = 40 tiles. */
    {
        u8 buf[TRUNK_SUB_MENU_MAX_CUSTOM * 20 + 1];
        u8 pos = 0;

        for (k = 0; k < gTrunkSubMenuCustomCount; k++) {
            const u8 *label = gTrunkSubMenuCustomOptions[k].label;
            u8 j = 0;

            while (j < 20 && label[j] != '\0')
                buf[pos++] = label[j++];
            while (j++ < 20)
                buf[pos++] = ' ';
        }
        buf[pos] = '\0';
        /* Tile index 141 = 21 + 3*40 = first tile of the 4th option line. */
        CopyStringTilesToVRAMBuffer(
            &gBgVram.cbb1[4512],
            buf, 0x900);
    }
}

/* ---- option handlers (vanilla equivalents) ---- */

static void TrunkSubMenu_SelectDetails(void) {
    gStatMod.card = GetNthCardOnScreen(2);
    gStatMod.field = FIELD_ARENA;
    gStatMod.stage = 0;
    SetCardInfoWithWarning(&gStatMod.card);
    PlayMusic(SFX_SELECT);
    ShowCardDetailView();
    sub_800A3D8(0);
    sub_800A3D8(2);
    sub_800AA58(1);
    sub_800ABA8();
    sub_8009364();
    TrunkSubMenu_RenderCustomOptions();
    TrunkSubMenu_SetCursorOam();
    SetVBlankCallback(TrunkSubMenu_VBlank);
    WaitForVBlank();
    LoadCharblock1();
}

static void TrunkSubMenu_SelectAddToDeck(void) {
    RunTrunkTask(7);
    sub_800A3D8(3);
    sub_800ABD0();
    sub_800AA58(6);
}

static void TrunkSubMenu_SelectRemoveFromDeck(void) {
    RunTrunkTask(8);
    sub_800A3D8(3);
    sub_800ABD0();
    sub_800AA58(6);
}

static void TrunkSubMenu_RefreshListPane(void) {
    sub_800A3D8(3);
    sub_800ABD0();
    sub_800AA58(6);
    TrunkSubMenu_RenderCustomOptions();
    TrunkSubMenu_SetCursorOam();
}

/* ---- custom options: Extra Deck ---- */

static const u8 kShowInEDeckLabel[] APPEND_TEXT = "Show in E. Deck      ";
static const u8 kMoveToEDeckLabel[] APPEND_TEXT = "Move to E. Deck      ";

/* Opens a deck-browser for the extra deck contents with a two-option
 * sub-menu on A press: "Details" (view card info) and "Return to Trunk"
 * (remove card from extra deck, restore to trunk qty). */
static void ExtraDeckViewer_Open(void) {
    u16 *extra = GetActiveExtraDeck();
    u8 savedDeckMenu[sizeof(gDeckMenu)];
    u8 count;
    u8 choice;

    count = GetExtraDeckSize();
    if (count == 0) {
        PlayMusic(SFX_FORBIDDEN);
        return;
    }

    DECKMENU_SAVE();

    do {
        u8 i;

        for (i = 0; i < EXTRA_DECK_SIZE; i++)
            gDeckMenu.cards[i] = extra[i];
        gDeckMenu.cost = 0;
        gDeckMenu.currentPos = 0;
        gDeckMenu.sortMode = 0;
        gDeckMenu.displayMode = 1;
        gDeckMenu.cardCount = GetExtraDeckSize();

        {
            /* ponytail: explicit stack init to avoid agbcc placing the
             * const array in .rodata (which the linker discards). */
            u8 labels[2];
            labels[0] = DECK_MENU_PICK_LABEL_DETAILS;
            labels[1] = DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK;
            choice = DeckMenuMainPickChosenLabel(labels, 2);
        }

        if (choice == DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK) {
            u16 cardId = gDeckMenu.cards[gDeckMenu.currentPos];

            if (ExtraDeck_TryRemoveCard(cardId) == TRUE) {
                if (GetTrunkQtyForCard(cardId) < TRUNK_CARD_LIMIT)
                    SetTrunkQtyForCard(cardId, GetTrunkQtyForCard(cardId) + 1);
                SyncCardOwnershipQty(cardId);
                RebuildVisibleTrunkCardList();
                PlayMusic(SFX_SELECT);
            }
        }
        /* DECK_MENU_PICK_LABEL_DETAILS stays in the picker loop.
         * DECK_MENU_PICK_RESULT_CANCEL exits via the while condition. */
    } while (choice == DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK
             && GetExtraDeckSize() > 0);

    DECKMENU_RESTORE();
}

static void TrunkSubMenu_ShowExtraDeck(void) {
    gTrunkSubMenuExitRequest = TRUE;
    ExtraDeckViewer_Open();
}

static void TrunkSubMenu_AddToExtraDeck(void) {
    u16 cardId = GetNthCardOnScreen(2);

    /* Safety check: registration should only show this for fusion cards */
    if (!IsFusionCard(cardId)) {
        PlayMusic(SFX_FORBIDDEN);
        return;
    }

    if (GetAvailableTrunkQty(cardId) == 0) {
        PlayMusic(SFX_FORBIDDEN);
        return;
    }

    if (GetExtraDeckSize() >= EXTRA_DECK_SIZE) {
        PlayMusic(SFX_FORBIDDEN);
        return;
    }

    TrunkMenu_DecrementTrunkQty(cardId);
    ExtraDeck_AddCard(cardId);
    SyncCardOwnershipQty(cardId);
    RebuildVisibleTrunkCardList();
    gTrunkSubMenuExitRequest = TRUE;
    PlayMusic(SFX_SELECT);
}

static void TrunkSubMenu_RegisterOptions(void) {
    gTrunkSubMenuCustomCount = 0;

    /* In extra deck view, no custom options needed */
    if (gTrunkExtraDeckViewActive)
        return;

    /* Option 4: Show in E. Deck (only when extra deck has cards) */
    if (GetExtraDeckSize() > 0) {
        gTrunkSubMenuCustomOptions[0].label  = kShowInEDeckLabel;
        gTrunkSubMenuCustomOptions[0].action = TrunkSubMenu_ShowExtraDeck;
        gTrunkSubMenuCustomCount = 1;
    }

    /* Option 5: Move to E. Deck (fusion cards only) */
    if (IsFusionCard(GetNthCardOnScreen(2))) {
        gTrunkSubMenuCustomOptions[gTrunkSubMenuCustomCount].label  = kMoveToEDeckLabel;
        gTrunkSubMenuCustomOptions[gTrunkSubMenuCustomCount].action = TrunkSubMenu_AddToExtraDeck;
        gTrunkSubMenuCustomCount++;
    }
}

/* ---- main sub-menu replacement ---- */

/* Trunk_A_Submenu is static in vanilla, so LYN_REPLACE_CHECK can't reference it. */
void Trunk_A_Submenu__Replacement(void) {
    unsigned keepProcessing;
    u8 totalCount;
    u8 actionExited = FALSE;

    /* Extra deck view: A directly removes card from extra deck and returns
     * it to the trunk, skipping the sub-menu entirely.  This mirrors the
     * graveyard trunk view where A has a single direct action. */
    if (gTrunkExtraDeckViewActive) {
        if (ExtraDeck_ReturnSelectedCardToTrunk() == TRUE) {
            sub_800A3D8(3);
            sub_800ABD0();
            sub_800AA58(6);
            PlayMusic(SFX_SELECT);
        } else {
            PlayMusic(SFX_FORBIDDEN);
            while (gPressedButtons & DPAD_RIGHT)
                WaitForVBlank();
        }
        /* ponytail: no sub-menu OAM to clear in this path */
        return;
    }

    TrunkSubMenu_RegisterOptions();
    totalCount = TrunkSubMenu_TotalOptionCount();

    gTrunkMenu.cursorState = 0;
    sub_8009364();
    TrunkSubMenu_RenderCustomOptions();
    TrunkSubMenu_SetCursorOam();
    LoadCharblock1();
    SetVBlankCallback(TrunkSubMenu_VBlank);
    WaitForVBlank();
    PlayMusic(SFX_SELECT);

    keepProcessing = 1;
    while (keepProcessing) {
        switch (TrunkSubmenuProcessInput()) {
        case NEW_B_BUTTON:
            keepProcessing = 0;
            break;
        case REPEAT_DPAD_UP:
            if (gTrunkMenu.cursorState > 0)
                gTrunkMenu.cursorState--;
            TrunkSubMenu_SetCursorOam();
            PlayMusic(SFX_MOVE_CURSOR);
            SetVBlankCallback(LoadOam);
            WaitForVBlank();
            break;
        case REPEAT_DPAD_DOWN:
            if (gTrunkMenu.cursorState < totalCount - 1)
                gTrunkMenu.cursorState++;
            TrunkSubMenu_SetCursorOam();
            PlayMusic(SFX_MOVE_CURSOR);
            SetVBlankCallback(LoadOam);
            WaitForVBlank();
            break;
        case NEW_A_BUTTON:
            switch (gTrunkMenu.cursorState) {
            case TRUNK_CURSOR_DETAILS:
                TrunkSubMenu_SelectDetails();
                break;
            case TRUNK_CURSOR_MOVE_TO_DECK:
                TrunkSubMenu_SelectAddToDeck();
                break;
            case TRUNK_CURSOR_MOVE_TO_TRUNK:
                TrunkSubMenu_SelectRemoveFromDeck();
                break;
            default: {
                u8 idx = gTrunkMenu.cursorState - TRUNK_CURSOR_CUSTOM_START;

                if (idx < gTrunkSubMenuCustomCount) {
                    gTrunkSubMenuCustomOptions[idx].action();
                    if (gTrunkSubMenuExitRequest) {
                        gTrunkSubMenuExitRequest = FALSE;
                        actionExited = TRUE;
                        keepProcessing = 0;
                    }
                }
                break;
            }
            }
            break;
        default:
            WaitForVBlank();
            break;
        }
    }
    TrunkSubMenu_ClearCursorOam();

    /* Refresh trunk display when a custom action changed view state. */
    if (actionExited) {
        sub_800A3D8(3);
        sub_800ABD0();
        sub_800AA58(6);
    } else {
        PlayMusic(SFX_CANCEL);
    }
}
