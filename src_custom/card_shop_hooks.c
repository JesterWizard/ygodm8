#include "global.h"
#include "configs/runtime.h"
#include "generated/card_trunk_generated.inc"

#define SHOP_BOARD_NUM_ROWS 5
#define SHOP_BOARD_NUM_COLS 7
#define SHOP_MAX_CARD_QTY 250

struct CardShopState {
  unsigned short* unk0[5][7];
  unsigned short unk8C[5][7];
  unsigned short unkD2[806];
  s16 firstVisibleRow;
  s16 numRows;
  s8 cursorColumn;
  s8 cursorRow;
  u8 unk724;
  u8 currentSortMode;
  u8 selectedMenuOption;
};

extern struct CardShopState sCardShop;
extern u16 gNewButtons;
extern u64 gMoney;
extern u8 gStartingShopCards[];
extern u8 gShopCardQty[];
extern u8 g80C9D84[];
extern u8 g80CA0B4[][5];
extern u8 g80CA0D7[];
extern const unsigned char g89A7F1E[][64];
extern const unsigned char g89A81DE[][64];
extern const unsigned char g89A849E[][64];
extern const unsigned char g89A875E[][64];
extern u16 gCustomShopCardList[];
extern u8 gDigitBufferU16[];

void InitNewGameShopCards(void);
void AddCardQtyToShop2(u16, u8);
void TrySellCard (void);
void sub_802CEE0 (int);
void sub_802D174 (void);
int sub_802DE84 (int);
void sub_802E270 (void);
void sub_802EA74 (void);
void sub_802FC88 (void);
void sub_802FD84 (u16);
void sub_802FE84 (int);
void sub_8030690 (void);
void sub_803096C (int);
void RemoveCardQtyFromPlayerInShop (u16, u8);
unsigned PlayerInShopHasAtLeastCardQty (u16, u8);
void AddCardQtyToShop (u16, u8);
void AddMoney (u64);
void ScalePriceToQty (void);
void SortCardsAccordingToContext(void);
void sub_802FF78(u8 *, u16);
void sub_802FFF0(u8 *, u16);

static void ClearShopStatTiles(u8 *dest) {
  CpuFill16(0, dest, 0x40);
  CpuFill16(0, dest + 0x40, 0x40);
}

static u16 GetShopCustomCardCount(void) {
  return gRuntimeConfig.enable_custom_cards_past_800 == TRUE ? NUM_CUSTOM_TRUNK_CARDS : 0;
}

static u16 GetShopCardCount(void) {
  return NUM_TRUE_CARDS + GetShopCustomCardCount();
}

static s16 GetShopNumRows(void) {
  return (GetShopCardCount() + SHOP_BOARD_NUM_COLS - 1) / SHOP_BOARD_NUM_COLS;
}

static u16 GetShopCardListCapacity(void) {
  return GetShopNumRows() * SHOP_BOARD_NUM_COLS + 1;
}

static s16 WrapShopRow(s16 row) {
  s16 numRows = sCardShop.numRows;

  if (row < 0)
    row += numRows;
  else if (row >= numRows)
    row -= numRows;
  return row;
}

static void CopyShopQtyToTemps(void) {
  u16 cardId;
  u16 i;

  for (cardId = 0; cardId < NUM_CARDS; cardId++) {
    gShopTempCardQty[cardId] = gShopCardQty[cardId];
    gPlayerTempCardQty[cardId] = gTrunkCardQty[cardId];
  }

  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    cardId = CUSTOM_CARD_START + i;
    gShopTempCardQty[cardId] = gShopCardQty[cardId];
    gPlayerTempCardQty[cardId] = gTrunkCardQty[cardId];
  }
}

static void CommitShopResults(void) {
  u16 cardId;
  u16 i;

  for (cardId = 0; cardId < NUM_CARDS; cardId++) {
    gShopCardQty[cardId] = gShopTempCardQty[cardId];
    gTrunkCardQty[cardId] = gPlayerTempCardQty[cardId];
  }

  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    cardId = CUSTOM_CARD_START + i;
    gShopCardQty[cardId] = gShopTempCardQty[cardId];
    gTrunkCardQty[cardId] = gPlayerTempCardQty[cardId];
    gCustomShopCardQty[i] = gShopCardQty[cardId];
    gCustomTrunkCardQty[i] = gTrunkCardQty[cardId];
    gCustomPlayerTempCardQty[i] = gPlayerTempCardQty[cardId];
  }
}

static void BuildShopCardList(void) {
  u16 i;
  u16 next = 1;
  u16 capacity = GetShopCardListCapacity();

  for (i = 0; i < capacity; i++)
    gCustomShopCardList[i] = CARD_NONE;

  for (i = 1; i < NUM_CARDS; i++)
    gCustomShopCardList[next++] = i;

#if NUM_CUSTOM_TRUNK_CARDS > 0
  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE)
    for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
      gCustomShopCardList[next++] = gCustomTrunkCards[i];
#endif
}

static void SortShopCardList(u8 sortOption, const u8 *sortModes) {
  gCardSortContext.cards = gCustomShopCardList + 1;
  gCardSortContext.cardCount = NUM_TRUE_CARDS;
  gCardSortContext.sortMode = sortModes[sortOption];
  SortCardsAccordingToContext();
  sCardShop.unk724 = 4;
  sCardShop.firstVisibleRow = sCardShop.numRows - 1;
}

static void SetShopRowPointers(void) {
  u8 i;
  u8 j;

  for (i = 0; i < SHOP_BOARD_NUM_ROWS; i++) {
    u8 row = g80CA0B4[sCardShop.unk724][i];
    for (j = 0; j < SHOP_BOARD_NUM_COLS; j++)
      sCardShop.unk0[i][j] = &sCardShop.unk8C[row][j];
  }
}

static void PopulateBuyShopRow(u8 row) {
  u8 col;
  s16 listRow = WrapShopRow(sCardShop.firstVisibleRow + row);

  for (col = 0; col < SHOP_BOARD_NUM_COLS; col++) {
    u16 cardId = gCustomShopCardList[listRow * SHOP_BOARD_NUM_COLS + col + 1];
    if (cardId != CARD_NONE && gShopTempCardQty[cardId] == 0)
      cardId = CARD_NONE;
    *sCardShop.unk0[row][col] = cardId;
  }
}

static void PopulateSellShopRow(u8 row) {
  u8 col;
  s16 listRow = WrapShopRow(sCardShop.firstVisibleRow + row);

  for (col = 0; col < SHOP_BOARD_NUM_COLS; col++) {
    u16 cardId = gCustomShopCardList[listRow * SHOP_BOARD_NUM_COLS + col + 1];
    if (cardId != CARD_NONE && gPlayerTempCardQty[cardId] == 0)
      cardId = CARD_NONE;
    *sCardShop.unk0[row][col] = cardId;
  }
}

static void PopulateAllBuyShopRows(void) {
  u8 row;

  for (row = 0; row < SHOP_BOARD_NUM_ROWS; row++)
    PopulateBuyShopRow(row);
}

static void PopulateAllSellShopRows(void) {
  u8 row;

  for (row = 0; row < SHOP_BOARD_NUM_ROWS; row++)
    PopulateSellShopRow(row);
}

static void InitShopState(void) {
  sCardShop.selectedMenuOption = 0;
  sCardShop.numRows = GetShopNumRows();
  sCardShop.firstVisibleRow = sCardShop.numRows - 1;
  sCardShop.unk724 = 4;
  sCardShop.currentSortMode = 0;
  sCardShop.cursorColumn = 0;
  sCardShop.cursorRow = 1;
}

/* LYN_REPLACEMENT(SetNextSortModeInSellShop) */
void SetNextSortModeInSellShop__Replacement(void) {
  if (++sCardShop.currentSortMode > 9)
    sCardShop.currentSortMode = 0;
  SortShopCardList(sCardShop.currentSortMode, g80C9D84);
}

/* LYN_REPLACEMENT(InitSellShop) */
void InitSellShop__Replacement(void) {
  CopyShopQtyToTemps();
  InitShopState();
  BuildShopCardList();
  SortShopCardList(0, g80C9D84);
  SetShopRowPointers();
  PopulateAllSellShopRows();
}

LYN_REPLACE_CHECK(sub_802CEE0);
void sub_802CEE0__Replacement(int row) {
  PopulateSellShopRow((u8)row);
}

/* LYN_REPLACEMENT(sub_802D190) */
void sub_802D190__Replacement(u8 sortOption) {
  SortShopCardList(sortOption, g80C9D84);
}

/* LYN_REPLACEMENT(UpdatePlayerShopSellResults) */
void UpdatePlayerShopSellResults__Replacement(void) {
  CommitShopResults();
}

/* LYN_REPLACEMENT(sub_802DAF8) */
void sub_802DAF8__Replacement(int row) {
  PopulateBuyShopRow((u8)row);
}

/* LYN_REPLACEMENT(SetNextSortModeInBuyShop) */
void SetNextSortModeInBuyShop__Replacement(void) {
  if (++sCardShop.currentSortMode > 9)
    sCardShop.currentSortMode = 0;
  SortShopCardList(sCardShop.currentSortMode, g80CA0D7);
}

/* LYN_REPLACEMENT(InitBuyShop) */
void InitBuyShop__Replacement(void) {
  CopyShopQtyToTemps();
  InitShopState();
  BuildShopCardList();
  SortShopCardList(0, g80CA0D7);
  SetShopRowPointers();
  PopulateAllBuyShopRows();
}

/* LYN_REPLACEMENT(UpdatePlayerShopBuyResults) */
void UpdatePlayerShopBuyResults__Replacement(void) {
  CommitShopResults();
}

/* LYN_REPLACEMENT(sub_802DFF8) */
void sub_802DFF8__Replacement(u8 sortOption) {
  SortShopCardList(sortOption, g80CA0D7);
}

LYN_REPLACE_CHECK(sub_802FF78);
void sub_802FF78__Replacement(u8 *dest, u16 cardId) {
  SetCardInfo(cardId);
  dest += 0x200;
  if (gCardInfo.atk == 0xFFFF) {
    ClearShopStatTiles(dest);
    return;
  }

  if (gCardInfo.atk / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.atk / 100, DIGIT_FLAG_NONE);

  CpuCopy16(g89A81DE[gDigitBufferU16[3]], dest, 0x40);
  CpuCopy16(g89A7F1E[gDigitBufferU16[4]], dest + 0x40, 0x40);
}

LYN_REPLACE_CHECK(sub_802FFF0);
void sub_802FFF0__Replacement(u8 *dest, u16 cardId) {
  SetCardInfo(cardId);
  dest += 0x280;
  if (gCardInfo.def == 0xFFFF) {
    ClearShopStatTiles(dest);
    return;
  }

  if (gCardInfo.def / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.def / 100, DIGIT_FLAG_NONE);

  CpuCopy16(g89A875E[gDigitBufferU16[3]], dest, 0x40);
  CpuCopy16(g89A849E[gDigitBufferU16[4]], dest + 0x40, 0x40);
}

LYN_REPLACE_CHECK(InitNewGameShopCards);
void InitNewGameShopCards__Replacement(void) {
  unsigned short cardId;
  unsigned short i;

  for (cardId = 0; cardId < NUM_CARDS; cardId++) {
    if (gRuntimeConfig.start_shop_with_one_copy_of_every_card == TRUE)
      gShopCardQty[cardId] = 1;
    else
      gShopCardQty[cardId] = gStartingShopCards[cardId];
  }

  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    if (gRuntimeConfig.start_shop_with_one_copy_of_every_card == TRUE)
      gShopCardQty[CUSTOM_CARD_START + i] = 1;
    else
      gShopCardQty[CUSTOM_CARD_START + i] = 0;

    gPlayerTempCardQty[CUSTOM_CARD_START + i] = gTrunkCardQty[CUSTOM_CARD_START + i];
    gCustomShopCardQty[i] = gShopCardQty[CUSTOM_CARD_START + i];
    gCustomPlayerTempCardQty[i] = gPlayerTempCardQty[CUSTOM_CARD_START + i];
  }
}

LYN_REPLACE_CHECK(AddCardQtyToShop2);
void AddCardQtyToShop2__Replacement(u16 cardId, u8 qty) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return;

  if (qty > SHOP_MAX_CARD_QTY - gShopCardQty[cardId])
    gShopCardQty[cardId] = SHOP_MAX_CARD_QTY;
  else
    gShopCardQty[cardId] += qty;

  if (cardId >= CUSTOM_CARD_START)
    gCustomShopCardQty[cardId - CUSTOM_CARD_START] = gShopCardQty[cardId];
}

LYN_REPLACE_CHECK(TrySellCard);
void TrySellCard__Replacement(void) {
  u16 cardId;
  u64 money;

  cardId = *sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn];
  if (PlayerInShopHasAtLeastCardQty(cardId, (gRuntimeConfig.allow_sell_one_copy_of_card == TRUE) ? 1 : 2) == 1) {
    money = gShopSelectedCard.sellPrice;
    RemoveCardQtyFromPlayerInShop(cardId, 1);
    AddMoney(money);
    AddCardQtyToShop(cardId, 1);
    PlayMusic(SFX_SELECT);
  }
  else {
    PlayMusic(0x39);
    sub_802E270();
    while (!(gNewButtons & (A_BUTTON | B_BUTTON)))
      WaitForVBlank();
    PlayMusic(SFX_CANCEL);
    sub_802FC88();
  }
  gShopSelectedCard.cardId = cardId;
  gShopSelectedCard.shopQty = gShopTempCardQty[cardId];
  ScalePriceToQty();
  sub_802D174();
  sub_802CEE0(sCardShop.cursorRow);
  sub_802FE84(sCardShop.cursorRow);
  sub_802EA74();
  sub_802FD84(*sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn]);
  SetVBlankCallback(sub_8030690);
  WaitForVBlank();
  sub_803096C(sub_802DE84(sCardShop.cursorRow));
}
