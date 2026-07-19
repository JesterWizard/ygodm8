#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "digit.h"
#include "card.h"
#include "text.h"
#include "duel.h"
#include "duel_helpers.h"
#include "deck_menu.h"
#include "money.h"
#include "gfx_reg_buffers.h"
#include "generated/card_trunk_generated.inc"
#include "generated/card_pack_assets_generated.inc"

#define SHOP_BOARD_NUM_ROWS 5
#define SHOP_BOARD_NUM_COLS 7
#define SHOP_MAX_CARD_QTY 250
#define SHOP_DPAD (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT)

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
extern struct ShopSelectedCard gShopSelectedCard;
extern u16 gNewButtons;
extern u16 gPressedButtons;
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
extern u8 g80CC0F4[];
extern u16 gCustomShopCardList[];
extern u8 gCustomShopTempCardQty[];
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
void sub_805742C (unsigned char *, unsigned short);
void sub_80576B4 (unsigned char *, unsigned short);
void sub_80576EC (unsigned char *, unsigned short);
void RemoveCardQtyFromPlayerInShop (u16, u8);
unsigned PlayerInShopHasAtLeastCardQty (u16, u8);
void AddCardQtyToShop (u16, u8);
void RemoveCardQtyFromShop (u16, u8);
unsigned char ShopHasSpaceForCardQty (u16, u8);
unsigned ShopHasAtLeastQtyOfCard (u16, u8);
unsigned PlayerInShopHasSpaceForCardQty (u16, u8);
void AddCardQtyToPlayerInShop (u16, u8);
void AddMoney (u64);
void ScalePriceToQty (void);
void SortCardsAccordingToContext(void);
void sub_802FF78(u8 *, u16);
void sub_802FFF0(u8 *, u16);
void SyncCustomTrunkCardQtyMirror(u16 cardId);
void SanitizeCustomCardQtyBuffers(void);
void PlayMusic(int);

typedef void (*ShopVoidFn)(void);
typedef void (*ShopU8Fn)(u8);
typedef int (*ShopProcessInputFn)(void);

/* Vanilla buy-shop helpers (static in card_shop.c). */
static ShopVoidFn const FadeToBlackBuyShop = (ShopVoidFn)0x0802C1D5;
static ShopVoidFn const GoOneRowUpInBuyShop = (ShopVoidFn)0x0802C2A1;
static ShopVoidFn const GoOneRowDownInBuyShop = (ShopVoidFn)0x0802C319;
static ShopVoidFn const GoOneColLeftInBuyShop = (ShopVoidFn)0x0802C391;
static ShopVoidFn const GoOneColRightInBuyShop = (ShopVoidFn)0x0802C409;
static ShopVoidFn const GoTenRowsUpInBuyShop = (ShopVoidFn)0x0802C481;
static ShopVoidFn const GoTenRowsDownInBuyShop = (ShopVoidFn)0x0802C4F9;
static ShopVoidFn const MoveCursorUpInBuyShop = (ShopVoidFn)0x0802DDD9;
static ShopVoidFn const MoveCursorDownInBuyShop = (ShopVoidFn)0x0802DE1D;
static ShopVoidFn const MoveCursorLeftInBuyShop = (ShopVoidFn)0x0802DA1D;
static ShopVoidFn const MoveCursorRightInBuyShop = (ShopVoidFn)0x0802DA8D;
static ShopVoidFn const MoveTenRowsUpInBuyShop = (ShopVoidFn)0x0802DE61;
static ShopVoidFn const MoveTenRowsDownInBuyShop = (ShopVoidFn)0x0802DE75;
static ShopVoidFn const sub_802DF1C = (ShopVoidFn)0x0802DF1D;
static ShopVoidFn const sub_802DF88 = (ShopVoidFn)0x0802DF89;
static ShopVoidFn const OpenConfirmBuyMenu = (ShopVoidFn)0x0802D5D5;
static ShopVoidFn const OpenSortSelectMenuInBuyShop = (ShopVoidFn)0x0803030D;
static ShopVoidFn const ToggleSortModeInBuyShop = (ShopVoidFn)0x0802C14D;
static ShopVoidFn const sub_802E1D8 = (ShopVoidFn)0x0802E1D9;
static ShopVoidFn const sub_802E868 = (ShopVoidFn)0x0802E869;
static ShopVoidFn const sub_802F9E8 = (ShopVoidFn)0x0802F9E9;
static ShopU8Fn const sub_802FCF0 = (ShopU8Fn)0x0802FCF1;
static ShopVoidFn const sub_802FE00 = (ShopVoidFn)0x0802FE01;
static ShopVoidFn const sub_802FE68 = (ShopVoidFn)0x0802FE69;
static ShopVoidFn const sub_8030068 = (ShopVoidFn)0x08030069;
static ShopVoidFn const sub_8030090 = (ShopVoidFn)0x08030091;
static ShopVoidFn const sub_803060C = (ShopVoidFn)0x0803060D;
static ShopVoidFn const sub_8030654 = (ShopVoidFn)0x08030655;
static ShopVoidFn const sub_8030684 = (ShopVoidFn)0x08030685;
static ShopVoidFn const sub_8030760 = (ShopVoidFn)0x08030761;
static ShopVoidFn const sub_8030898 = (ShopVoidFn)0x08030899;
static ShopVoidFn const DrawBuyShopSellPrice = (ShopVoidFn)0x0802EB65; /* sub_802EB64 */
static ShopVoidFn const DrawBuyShopMoneyLeft = (ShopVoidFn)0x0802EE35; /* sub_802EE34 */
static ShopVoidFn const SetBgDimEffectLow = (ShopVoidFn)0x0802FBF5;
static ShopProcessInputFn const ProcessInputBuyShop = (ShopProcessInputFn)0x0802C0BD;

typedef void (*ShopCardIdFn)(u16);
static ShopCardIdFn const sub_802FD48 = (ShopCardIdFn)0x0802FD49;

extern u16 gOamBuffer[];
extern u16 g80CB3D4[][30];

/* EWRAM — APPEND_DATA is ROM; a ROM flag never sticks and only the palette swap ran. */
extern u8 gBuyShopPackView;
extern u8 gBuyShopPackStock[];

u16 RandRangeU16(u16 min, u16 max);

static unsigned IsSelectedCardUnbuyable(void) {
  typedef unsigned (*Fn)(void);
  return ((Fn)0x0802C571)();
}

void sub_802FF78__Replacement(u8 *dest, u16 cardId);
void sub_802FFF0__Replacement(u8 *dest, u16 cardId);
void InitBuyShop__Replacement(void);
void UpdatePlayerShopBuyResults__Replacement(void);
void sub_802FB08__Replacement(void);
unsigned PlayerInShopHasSpaceForCardQty__Replacement(u16 cardId, u8 qty);
void AddCardQtyToPlayerInShop__Replacement(u16 cardId, u8 qty);

static u8 IsCustomShopCardId(u16 cardId) {
  return cardId >= CUSTOM_CARD_START && cardId - CUSTOM_CARD_START < NUM_CUSTOM_CARDS;
}

u8 GetShopCardQty(u16 cardId) {
  if (IsCustomShopCardId(cardId))
    return gCustomShopCardQty[cardId - CUSTOM_CARD_START];
  if (cardId < NUM_CARDS)
    return gShopCardQty[cardId];
  return 0;
}

void SetShopCardQty(u16 cardId, u8 qty) {
  if (IsCustomShopCardId(cardId))
    gCustomShopCardQty[cardId - CUSTOM_CARD_START] = qty;
  else if (cardId < NUM_CARDS)
    gShopCardQty[cardId] = qty;
}

u8 GetShopTempCardQty(u16 cardId) {
  if (IsCustomShopCardId(cardId))
    return gCustomShopTempCardQty[cardId - CUSTOM_CARD_START];
  if (cardId < NUM_CARDS)
    return gShopTempCardQty[cardId];
  return 0;
}

void SetShopTempCardQty(u16 cardId, u8 qty) {
  if (IsCustomShopCardId(cardId))
    gCustomShopTempCardQty[cardId - CUSTOM_CARD_START] = qty;
  else if (cardId < NUM_CARDS)
    gShopTempCardQty[cardId] = qty;
}

u8 GetPlayerTempCardQty(u16 cardId) {
  if (IsCustomShopCardId(cardId))
    return gCustomPlayerTempCardQty[cardId - CUSTOM_CARD_START];
  if (cardId < NUM_CARDS)
    return gPlayerTempCardQty[cardId];
  return 0;
}

void SetPlayerTempCardQty(u16 cardId, u8 qty) {
  if (IsCustomShopCardId(cardId))
    gCustomPlayerTempCardQty[cardId - CUSTOM_CARD_START] = qty;
  else if (cardId < NUM_CARDS)
    gPlayerTempCardQty[cardId] = qty;
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

/*
 * Match vanilla GoTenRows: never DMA shop VRAM mid-frame.
 * sub_8030898 = LoadBgOffsets + 5 card rows + PLTT 0xB0 + UI tiles.
 */
static void CommitBuyShopPackFrame(void) {
  sub_8030068();
  SetVBlankCallback(sub_8030684);
  WaitForVBlank();
  sub_8030898();
}

/* Pack spans two list rows; id = packRow*7+col. */
static u16 GetSelectedPackId(void) {
  s16 listRow = WrapShopRow((s16)(sCardShop.firstVisibleRow + sCardShop.cursorRow));

  return (u16)((listRow / 2) * SHOP_BOARD_NUM_COLS + sCardShop.cursorColumn);
}

/*
 * Pack HUD: Money + Domino / Sell + Domino / Left + Domino on the right;
 * Shop/<stock> on the top-left (drawn after EA74 — Money's leftward clear
 * would otherwise wipe Shop down to a lone "S").
 * Name: vanilla 15-char large font only (small font overflows cbb3 → green BG1).
 */
static void ApplyBuyShopPackHud(void) {
  u8 row;
  u8 i;
  u8 j;
  u8 r4;
  u16 *ptr;
  u16 tile;
  u8 buffer[40];
  u8 startCol;
  u16 packId;
  const u8 *name;
  u8 stock;

  for (i = 0; i < 4; i++)
    CpuCopy16(g80CB3D4[i], gBgVram.sbb1F[i], 60);

  for (row = 17; row < 20; row++)
    for (j = 0; j < 30; j++)
      gBgVram.sbb1F[row][j] = 0xD000;

  gBgVram.sbb1F[1][2] = 0xD000;
  gBgVram.sbb1F[1][3] = 0xD000;
  gBgVram.sbb1F[2][2] = 0xD000;
  gBgVram.sbb1F[2][3] = 0xD000;

  CpuFill16(0, gBgVram.sbb1E[24] + 16, 0x1E0);
  CpuFill16(0, ((struct Cbb *)&gBgVram)->cbb3 + 0x3520, 0x100);

  packId = GetSelectedPackId();
  if (packId >= NUM_CARD_PACKS) {
    sub_802EA74();
    return;
  }

  stock = gBuyShopPackStock[packId];
  name = sCardPackNames[packId];

  gShopSelectedCard.buyPrice = sCardPackPrices[packId];
  SetCardInfo(1);
  sub_802EA74();

  /* Domino suffix on money row (tiles 0x1A3–0x1A8, same as Sell/Left). */
  ptr = &gBgVram.sbb1F[1][29];
  *ptr-- = 0xD1A8;
  *ptr-- = 0xD1A7;
  *ptr-- = 0xD1A6;
  *ptr-- = 0xD1A5;
  *ptr-- = 0xD1A4;
  *ptr = 0xD1A3;

  DrawBuyShopSellPrice();
  DrawBuyShopMoneyLeft();

  /* Shop/<qty> after EA74 so leftward Money clear cannot erase it. */
  ptr = &gBgVram.sbb1F[1][1];
  tile = 0xD152;
  for (i = 0; i < 6; i++)
    *ptr++ = tile + i;
  *ptr++ = 0xD182;
  ConvertU16ToDigitBuffer(stock, DIGIT_FLAG_ALIGN_LEFT);
  for (j = 0; j < 3 && gDigitBufferU16[j] != DIGIT_TERMINATOR; j++)
    *ptr++ = 0xD000 | (gDigitBufferU16[j] + 0x195);

  r4 = 0;
  j = 0;
  while (j < 15 && name[j]) {
    buffer[r4++] = name[j++];
  }
  for (; j < 16; r4++, j++)
    buffer[r4] = 0;

  CopyStringTilesToVRAMBuffer(gBgVram.sbb1E[24] + 16, buffer, 0x801);

  j = 0;
  while (j < 15 && name[j])
    j++;
  startCol = (u8)((30 - j) / 2);
  ptr = &gBgVram.sbb1F[19][startCol];
  for (i = 0; i < j; i++)
    ptr[i] = 0xD000 | (0x1B1 + i);
}

static void RestoreBuyShopChromeTilemap(void) {
  u8 i;

  for (i = 0; i < 20; i++)
    CpuCopy16(g80CB3D4[i], gBgVram.sbb1F[i], 60);
}

/* Buffer-only UI update. Caller must CommitBuyShopPackFrame (or equiv) after. */
static void RefreshBuyShopSelectionUi(void) {
  u16 cardId = *sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn];

  gShopSelectedCard.cardId = cardId;
  gShopSelectedCard.shopQty = GetShopTempCardQty(cardId);
  ScalePriceToQty();
  if (gBuyShopPackView) {
    /* Never call FD48 in pack view — it paints Money/Sell/Left + bottom stats. */
    ApplyBuyShopPackHud();
  } else {
    sub_802FD48(cardId);
  }
  sub_802FB08__Replacement();
}

/* ROM tables — not linker symbols (only referenced from naked asm). */
static u16 const *const sShopCursorY = (u16 const *)0x080CDE5A;
static u16 const *const sShopCursorX = (u16 const *)0x080CDE64;

/*
 * LYN_REPLACEMENT(sub_802FB08)
 * Vanilla bottoms use +0x1E within one mini-card slot. Packs span two slots:
 * bottom corners sit at the lower slot's vanilla bottom (row+1 Y + 0x1E).
 * A flat +0x3A from row0's wrapped Y (0xF1) lands mid-pack on screen.
 */
void sub_802FB08__Replacement(void) {
  u32 *oam = (u32 *)gOamBuffer;
  u8 col = (u8)sCardShop.cursorColumn;
  u8 row = (u8)sCardShop.cursorRow;
  u32 x = sShopCursorX[col];
  u32 yTop = sShopCursorY[row] & 0xFF;
  u32 yBot;
  u32 xHi = (x + 0x1E) & 0x1FF;

  if (gBuyShopPackView) {
    if (row < 4)
      yBot = (sShopCursorY[row + 1] + 0x1E) & 0xFF;
    else
      yBot = (yTop + 0x3E) & 0xFF;
  } else {
    yBot = (sShopCursorY[row] + 0x1E) & 0xFF;
  }

  /* Four corner sprites: TL, TR, BL, BR (same layout as vanilla asm). */
  oam[0] = ((x << 16) & 0x01FF0000) | yTop | 0x80000000;
  oam[1] = 0x8800;
  oam[2] = (xHi << 16) | yTop | 0x90000000;
  oam[3] = 0x8800;
  oam[4] = ((x << 16) & 0x01FF0000) | yBot | 0xA0000000;
  oam[5] = 0x8800;
  oam[6] = (xHi << 16) | yBot | 0xB0000000;
  oam[7] = 0x8800;
}

/* Pack spans 2 list rows; cursor must sit on the even (top) half. */
static void SnapCursorToPackTop(void) {
  s16 listRow = WrapShopRow((s16)(sCardShop.firstVisibleRow + sCardShop.cursorRow));

  if ((listRow & 1) == 0)
    return;
  if (sCardShop.cursorRow > 0)
    sCardShop.cursorRow--;
  else
    sCardShop.firstVisibleRow = WrapShopRow((s16)(sCardShop.firstVisibleRow - 1));
}

static void InitBuyShopPackStock(void) {
  u8 i;

  for (i = 0; i < NUM_CARD_PACKS && i < 16; i++)
    gBuyShopPackStock[i] = sCardPackStockDefault[i];
}

static void RestoreBuyShopGraphicsAfterReveal(void) {
  FadeToBlackBuyShop();
  sub_802E1D8();
  sub_802E868();
  sub_802FE00();
  sub_8030090();
  sub_802F9E8();
  SnapCursorToPackTop();
  sub_802FE68();
  RefreshBuyShopSelectionUi();
  sub_8030068();
  SetVBlankCallback(sub_803060C);
  WaitForVBlank();
  SetBgDimEffectLow();
  SetVBlankCallback(sub_8030654);
  WaitForVBlank();
  sub_8030760(); /* LoadVRAM — packs + HUD buffers */
}

/* Fade to a trunk/deck-style list of the 5 pulled cards. */
static void ShowPackReveal(const u16 *cards) {
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;

  FadeToBlackBuyShop();

  DECKMENU_SAVE();
  for (i = 0; i < DECK_SIZE; i++)
    gDeckMenu.cards[i] = CARD_NONE;
  for (i = 0; i < CARD_PACK_REVEAL_COUNT; i++)
    gDeckMenu.cards[i] = cards[i];
  CardListViewerOpenLoaded(CARD_PACK_REVEAL_COUNT);
  DECKMENU_RESTORE();

  RestoreBuyShopGraphicsAfterReveal();
}

static void TryBuyCardPack(void) {
  u16 packId = GetSelectedPackId();
  u16 cards[CARD_PACK_REVEAL_COUNT];
  u16 poolOff;
  u16 poolLen;
  u16 price;
  u8 i;

  if (packId >= NUM_CARD_PACKS || gBuyShopPackStock[packId] == 0) {
    PlayMusic(0x39);
    WaitForVBlank();
    return;
  }

  price = sCardPackPrices[packId];
  if (!CanAfford(price)) {
    PlayMusic(0x39);
    WaitForVBlank();
    return;
  }

  poolOff = sCardPackPoolOff[packId];
  poolLen = (u16)(sCardPackPoolOff[packId + 1] - poolOff);
  if (poolLen == 0) {
    PlayMusic(0x39);
    WaitForVBlank();
    return;
  }

  for (i = 0; i < CARD_PACK_REVEAL_COUNT; i++) {
    cards[i] = sCardPackPoolCards[poolOff + RandRangeU16(0, poolLen - 1)];
    if (!PlayerInShopHasSpaceForCardQty__Replacement(cards[i], 1)) {
      PlayMusic(0x39);
      WaitForVBlank();
      return;
    }
  }

  RemoveMoney(price);
  gBuyShopPackStock[packId]--;
  for (i = 0; i < CARD_PACK_REVEAL_COUNT; i++)
    AddCardQtyToPlayerInShop__Replacement(cards[i], 1);

  ShowPackReveal(cards);
}

/* Pack-mode D-pad: move without vanilla GoOne* (avoids FD48 Money/Sell/Left flash). */
static void NavigateBuyShopPack(u8 dir) {
  switch (dir) {
    case 0: /* up — one pack = two list rows */
      MoveCursorUpInBuyShop();
      MoveCursorUpInBuyShop();
      break;
    case 1:
      MoveCursorDownInBuyShop();
      MoveCursorDownInBuyShop();
      break;
    case 2:
      MoveCursorLeftInBuyShop();
      break;
    case 3:
      MoveCursorRightInBuyShop();
      break;
    case 4:
      MoveTenRowsUpInBuyShop();
      MoveTenRowsUpInBuyShop();
      sub_802DF1C();
      sub_802DF88();
      break;
    case 5:
      MoveTenRowsDownInBuyShop();
      MoveTenRowsDownInBuyShop();
      sub_802DF1C();
      sub_802DF88();
      break;
  }
  SnapCursorToPackTop();
  sub_802FE68();
  RefreshBuyShopSelectionUi();
  CommitBuyShopPackFrame();
}

static void ToggleBuyShopPackView(void) {
  gBuyShopPackView ^= 1;
  if (gBuyShopPackView) {
    SnapCursorToPackTop();
  } else {
    RestoreBuyShopChromeTilemap();
    sub_802EA74();
    sub_802FCF0(sCardShop.currentSortMode);
  }
  sub_802FE68();
  RefreshBuyShopSelectionUi();
  CommitBuyShopPackFrame();
}

/* Unique pack per PNG: packId = packRow*7+col; empty past NUM_CARD_PACKS. */
static void DrawBuyShopPackRow(int displayRow) {
  u8 i;
  u8 bufRow = (u8)sub_802DE84((u8)displayRow);
  u8 *dest = &gBgVram.cbb0[0x40 + bufRow * 0x1C00];
  s16 listRow = WrapShopRow((s16)(sCardShop.firstVisibleRow + displayRow));
  u8 bottomHalf = (u8)(listRow & 1);
  u16 packRow = (u16)(listRow / 2);

  for (i = 0; i < SHOP_BOARD_NUM_COLS; dest += CARD_PACK_HALF_BYTES, i++) {
    u16 packId = (u16)(packRow * SHOP_BOARD_NUM_COLS + i);

    if (packId >= NUM_CARD_PACKS)
      CpuCopy16(g80CC0F4, dest, CARD_PACK_HALF_BYTES);
    else
      CpuCopy16(sCardPackGfx[packId] + bottomHalf * CARD_PACK_HALF_BYTES, dest,
                CARD_PACK_HALF_BYTES);
  }
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
    gCustomShopTempCardQty[i] = GetShopCardQty(cardId);
    gCustomPlayerTempCardQty[i] = gCustomTrunkCardQty[i];
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
    gCustomShopCardQty[i] = gCustomShopTempCardQty[i];
    gCustomTrunkCardQty[i] = gCustomPlayerTempCardQty[i];
    SyncCustomTrunkCardQtyMirror(cardId);
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
  gCardSortContext.cardCount = gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE ? GetShopCardCount() : NUM_TRUE_CARDS;
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
    if (cardId != CARD_NONE && GetShopTempCardQty(cardId) == 0)
      cardId = CARD_NONE;
    *sCardShop.unk0[row][col] = cardId;
  }
}

static void PopulateSellShopRow(u8 row) {
  u8 col;
  s16 listRow = WrapShopRow(sCardShop.firstVisibleRow + row);

  for (col = 0; col < SHOP_BOARD_NUM_COLS; col++) {
    u16 cardId = gCustomShopCardList[listRow * SHOP_BOARD_NUM_COLS + col + 1];
    if (cardId != CARD_NONE && GetPlayerTempCardQty(cardId) == 0)
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
  gBuyShopPackView = 0;
  InitBuyShopPackStock();
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
  if (gCardInfo.atk == 0xFFFF)
    return;

  if (gCardInfo.atk / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.atk / 100, DIGIT_FLAG_NONE);

  CpuCopy16(g89A81DE[gDigitBufferU16[3]], dest, 0x40);
  CpuCopy16(g89A7F1E[gDigitBufferU16[4]], dest + 0x40, 0x40);
}

LYN_REPLACE_CHECK(sub_802FE84);
void sub_802FE84__Replacement(int displayRow) {
  u8 i;
  u8 bufRow;
  u8 *dest;

  if (gBuyShopPackView) {
    DrawBuyShopPackRow(displayRow);
    return;
  }

  bufRow = (u8)sub_802DE84((u8)displayRow);
  dest = &gBgVram.cbb0[0x40 + bufRow * 0x1C00];
  for (i = 0; i < SHOP_BOARD_NUM_COLS; dest += 0x400, i++) {
    u16 cardId = sCardShop.unk8C[bufRow][i];
    if (cardId == CARD_NONE)
      CpuCopy16(g80CC0F4, dest, 0x400);
    else {
      sub_805742C(dest, cardId);
      sub_80576EC(dest, cardId);
      sub_80576B4(dest, cardId);
      sub_802FF78__Replacement(dest, cardId);
      sub_802FFF0__Replacement(dest, cardId);
    }
  }
}

LYN_REPLACE_CHECK(CardShopBuyMain);
void CardShopBuyMain__Replacement(void) {
  unsigned short cardId;
  unsigned keepProcessing;

  FadeToBlackBuyShop();
  InitBuyShop__Replacement();
  cardId = *sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn];
  gShopSelectedCard.cardId = cardId;
  gShopSelectedCard.shopQty = GetShopTempCardQty(cardId);
  ScalePriceToQty();
  sub_802E1D8();
  sub_802E868();
  sub_802FD48(cardId);
  sub_802FE00();
  sub_8030090();
  sub_802F9E8();
  sub_8030068();
  SetVBlankCallback(sub_803060C);
  WaitForVBlank();
  SetBgDimEffectLow();
  SetVBlankCallback(sub_8030654);
  WaitForVBlank();
  sub_8030760();
  keepProcessing = 1;
  while (keepProcessing) {
    if (gRuntimeConfig.enable_shop_card_pack_view == TRUE
        && (gNewButtons & R_BUTTON)
        && !(gPressedButtons & SHOP_DPAD)) {
      ToggleBuyShopPackView();
      PlayMusic(SFX_SELECT);
      WaitForVBlank();
      continue;
    }

    switch ((unsigned short)ProcessInputBuyShop()) {
      case REPEAT_DPAD_UP:
        if (gBuyShopPackView)
          NavigateBuyShopPack(0);
        else
          GoOneRowUpInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case REPEAT_DPAD_DOWN:
        if (gBuyShopPackView)
          NavigateBuyShopPack(1);
        else
          GoOneRowDownInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case REPEAT_DPAD_LEFT:
        if (gBuyShopPackView)
          NavigateBuyShopPack(2);
        else
          GoOneColLeftInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case REPEAT_DPAD_RIGHT:
        if (gBuyShopPackView)
          NavigateBuyShopPack(3);
        else
          GoOneColRightInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case REPEAT_DPAD_UP | REPEAT_R_BUTTON:
        if (gBuyShopPackView)
          NavigateBuyShopPack(4);
        else
          GoTenRowsUpInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case REPEAT_DPAD_DOWN | REPEAT_R_BUTTON:
        if (gBuyShopPackView)
          NavigateBuyShopPack(5);
        else
          GoTenRowsDownInBuyShop();
        PlayMusic(SFX_MOVE_CURSOR);
        break;
      case NEW_A_BUTTON:
        if (gBuyShopPackView)
          TryBuyCardPack();
        else if (!IsSelectedCardUnbuyable())
          OpenConfirmBuyMenu();
        else {
          PlayMusic(0x39);
          WaitForVBlank();
        }
        break;
      case NEW_B_BUTTON:
        keepProcessing = 0;
        PlayMusic(SFX_CANCEL);
        WaitForVBlank();
        break;
      case NEW_START_BUTTON:
        OpenSortSelectMenuInBuyShop();
        break;
      case NEW_SELECT_BUTTON:
        ToggleSortModeInBuyShop();
        PlayMusic(SFX_SELECT);
        break;
      default:
        WaitForVBlank();
        break;
    }
  }
  UpdatePlayerShopBuyResults__Replacement();
  FadeToBlackBuyShop();
}

LYN_REPLACE_CHECK(sub_802FFF0);
void sub_802FFF0__Replacement(u8 *dest, u16 cardId) {
  SetCardInfo(cardId);
  dest += 0x280;
  if (gCardInfo.def == 0xFFFF)
    return;

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

  SanitizeCustomCardQtyBuffers();

  for (cardId = 0; cardId < NUM_CARDS; cardId++) {
    if (gRuntimeConfig.start_shop_with_one_copy_of_every_card == TRUE)
      gShopCardQty[cardId] = 1;
    else
      gShopCardQty[cardId] = gStartingShopCards[cardId];
  }

  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    cardId = CUSTOM_CARD_START + i;
    if (gRuntimeConfig.start_shop_with_one_copy_of_every_card == TRUE)
      SetShopCardQty(cardId, 1);
    else
      SetShopCardQty(cardId, 0);

    gCustomPlayerTempCardQty[i] = gCustomTrunkCardQty[i];
  }
}

LYN_REPLACE_CHECK(AddCardQtyToShop2);
void AddCardQtyToShop2__Replacement(u16 cardId, u8 qty) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return;

  if (qty > SHOP_MAX_CARD_QTY - GetShopCardQty(cardId))
    SetShopCardQty(cardId, SHOP_MAX_CARD_QTY);
  else
    SetShopCardQty(cardId, GetShopCardQty(cardId) + qty);
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
  gShopSelectedCard.shopQty = GetShopTempCardQty(cardId);
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

LYN_REPLACE_CHECK(AddCardQtyToShop);
void AddCardQtyToShop__Replacement(u16 cardId, u8 qty) {
  u8 current;

  if (cardId == CARD_NONE)
    return;

  current = GetShopTempCardQty(cardId);
  if (qty > SHOP_MAX_CARD_QTY - current)
    SetShopTempCardQty(cardId, SHOP_MAX_CARD_QTY);
  else
    SetShopTempCardQty(cardId, current + qty);
}

LYN_REPLACE_CHECK(ShopHasSpaceForCardQty);
unsigned char ShopHasSpaceForCardQty__Replacement(u16 cardId, u8 qty) {
  if (qty > SHOP_MAX_CARD_QTY - GetShopTempCardQty(cardId))
    return 0;
  return 1;
}

LYN_REPLACE_CHECK(RemoveCardQtyFromPlayerInShop);
void RemoveCardQtyFromPlayerInShop__Replacement(u16 cardId, u8 qty) {
  u8 current;

  if (cardId == CARD_NONE)
    return;

  current = GetPlayerTempCardQty(cardId);
  if (qty > current)
    SetPlayerTempCardQty(cardId, 0);
  else
    SetPlayerTempCardQty(cardId, current - qty);
}

LYN_REPLACE_CHECK(PlayerInShopHasAtLeastCardQty);
unsigned PlayerInShopHasAtLeastCardQty__Replacement(u16 cardId, u8 qty) {
  if (qty > GetPlayerTempCardQty(cardId))
    return 0;
  return 1;
}

LYN_REPLACE_CHECK(PlayerInShopHasSpaceForCardQty);
unsigned PlayerInShopHasSpaceForCardQty__Replacement(u16 cardId, u8 qty) {
  if (qty > SHOP_MAX_CARD_QTY - GetPlayerTempCardQty(cardId))
    return 0;
  return 1;
}

LYN_REPLACE_CHECK(AddCardQtyToPlayerInShop);
void AddCardQtyToPlayerInShop__Replacement(u16 cardId, u8 qty) {
  u8 current;

  if (!cardId)
    return;

  current = GetPlayerTempCardQty(cardId);
  if (qty > SHOP_MAX_CARD_QTY - current)
    SetPlayerTempCardQty(cardId, SHOP_MAX_CARD_QTY);
  else
    SetPlayerTempCardQty(cardId, current + qty);
}

LYN_REPLACE_CHECK(RemoveCardQtyFromShop);
void RemoveCardQtyFromShop__Replacement(u16 cardId, u8 qty) {
  u8 current;

  if (cardId == CARD_NONE)
    return;

  current = GetShopTempCardQty(cardId);
  if (qty > current)
    SetShopTempCardQty(cardId, 0);
  else
    SetShopTempCardQty(cardId, current - qty);
}

LYN_REPLACE_CHECK(ShopHasAtLeastQtyOfCard);
unsigned ShopHasAtLeastQtyOfCard__Replacement(u16 cardId, u8 qty) {
  if (qty > GetShopTempCardQty(cardId))
    return 0;
  return 1;
}
