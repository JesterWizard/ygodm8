#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "duel.h"
#include "gfx_reg_buffers.h"
#include "text.h"

/*
 * Status screen layout — edit row/col in this block.
 * Stat numbers and StatusMenu entry are LynJump-replaced below.
 */

/* Bottom row of a tall (2-row) digit — always VALUE_ROW + 1. */
#define STATUS_VALUE_BOTTOM_ROW(valueRow) ((valueRow) + 1)

/* -------------------------------------------------------------------------- */
/* Top panel — player name (top-left, under the "Name" label)                 */
/* asm: StatusMenu name loops @ 0x0800762E, 0x08007652, 0x0800767C           */
/* Data: g8DF811C (per-character tile ids from save)                          */
/* -------------------------------------------------------------------------- */

#define STATUS_PLAYER_NAME_LINE1_ROW    1
#define STATUS_PLAYER_NAME_LINE1_COL    2
#define STATUS_PLAYER_NAME_LINE1_CHARS  7
#define STATUS_PLAYER_NAME_LINE2_ROW    2
#define STATUS_PLAYER_NAME_LINE2_COL    2
#define STATUS_PLAYER_NAME_LINE2_CHARS  3
#define STATUS_PLAYER_NAME_LINE3_ROW    3
#define STATUS_PLAYER_NAME_LINE3_COL    3
#define STATUS_PLAYER_NAME_LINE3_CHARS  8

/* -------------------------------------------------------------------------- */
/* Title labels (small text baked into gUnk_8088778; reposition in C here)    */
/* Tile indices must match CopyStringTilesToVRAMBuffer charBuf offsets below. */
/* -------------------------------------------------------------------------- */

#define STATUS_LABEL_PALETTE 0xF000
/* First map tile for char 0 loaded at charOffset (one 32-byte tile per glyph). */
#define STATUS_LABEL_TILE_BASE(charOffset) ((u16)((charOffset) / 32))

#define STATUS_NAME_LABEL_ROW         2
#define STATUS_NAME_LABEL_COL         2
#define STATUS_NAME_LABEL_VANILLA_ROW 2
#define STATUS_NAME_LABEL_VANILLA_COL 2
#define STATUS_NAME_LABEL_TILES       3
#define STATUS_NAME_LABEL_TILE_BASE 0x031
#define STATUS_NAME_LABEL_CHAR_OFFSET 0x320

#define STATUS_DECK_CAPACITY_LABEL_ROW         1
#define STATUS_DECK_CAPACITY_LABEL_COL        13
#define STATUS_DECK_CAPACITY_LABEL_VANILLA_ROW 2
#define STATUS_DECK_CAPACITY_LABEL_VANILLA_COL 13
#define STATUS_DECK_CAPACITY_LABEL_VANILLA_TILES 9
#define STATUS_DECK_CAPACITY_WORD1_TILES       4
#define STATUS_DECK_CAPACITY_WORD2_TILES       8
#define STATUS_DECK_CAPACITY_WORD2_CHAR_INDEX  5
#define STATUS_DECK_CAPACITY_LABEL_CHAR_OFFSET 0x680

#define STATUS_DUELIST_LEVEL_LABEL_ROW         6
#define STATUS_DUELIST_LEVEL_LABEL_COL         2
#define STATUS_DUELIST_LEVEL_LABEL_VANILLA_ROW 6
#define STATUS_DUELIST_LEVEL_LABEL_VANILLA_COL 2
#define STATUS_DUELIST_LEVEL_LABEL_VANILLA_TILES 9
#define STATUS_DUELIST_LEVEL_WORD1_TILES       7
#define STATUS_DUELIST_LEVEL_WORD2_TILES       5
#define STATUS_DUELIST_LEVEL_WORD2_CHAR_INDEX  8
#define STATUS_DUELIST_LEVEL_LABEL_CHAR_OFFSET 0x400

#define STATUS_LIFE_POINTS_LABEL_ROW         6
#define STATUS_LIFE_POINTS_LABEL_COL        13
#define STATUS_LIFE_POINTS_LABEL_VANILLA_ROW 6
#define STATUS_LIFE_POINTS_LABEL_VANILLA_COL 13
#define STATUS_LIFE_POINTS_LABEL_VANILLA_TILES 8
#define STATUS_LIFE_POINTS_WORD1_TILES         4
#define STATUS_LIFE_POINTS_WORD2_TILES         6
#define STATUS_LIFE_POINTS_WORD2_CHAR_INDEX    5
#define STATUS_LIFE_POINTS_LABEL_CHAR_OFFSET 0x900

#define STATUS_MONEY_LABEL_ROW         16
#define STATUS_MONEY_LABEL_COL          1
#define STATUS_MONEY_LABEL_VANILLA_ROW 16
#define STATUS_MONEY_LABEL_VANILLA_COL  1
#define STATUS_MONEY_LABEL_TILES        3
#define STATUS_MONEY_LABEL_TILE_BASE 0x05E
#define STATUS_MONEY_LABEL_CHAR_OFFSET 0xD80

static const u8 sStatusDeckCapacityLabel[] APPEND_RODATA = "Deck Capacity";
static const u8 sStatusDuelistLevelLabel[] APPEND_RODATA = "Duelist Level";
static const u8 sStatusLifePointsLabel[] APPEND_RODATA = "Life Points";

/* -------------------------------------------------------------------------- */
/* Top panel — deck capacity number (top-right, e.g. "65000")                   */
/* LynJump: sub_8007AB8  |  value: gDeckCapacity                          */
/* -------------------------------------------------------------------------- */

#define STATUS_DECK_CAPACITY_VALUE_ROW    3
#define STATUS_DECK_CAPACITY_VALUE_COL   14
#define STATUS_DECK_CAPACITY_VALUE_DIGITS 5

/* -------------------------------------------------------------------------- */
/* Top panel — duelist level number (bottom-left, e.g. "999")                   */
/* LynJump: sub_80079C4  |  value: gDuelistLevel                          */
/* -------------------------------------------------------------------------- */

#define STATUS_DUELIST_LEVEL_VALUE_ROW    8
#define STATUS_DUELIST_LEVEL_VALUE_COL    3
#define STATUS_DUELIST_LEVEL_VALUE_DIGITS 4

/* -------------------------------------------------------------------------- */
/* Top panel — life points number (bottom-right, e.g. "8000")                   */
/* LynJump: sub_8007BB0  |  value: gLifePointsOutsideDuel                 */
/* -------------------------------------------------------------------------- */

#define STATUS_LIFE_POINTS_VALUE_ROW    8
#define STATUS_LIFE_POINTS_VALUE_COL   14
#define STATUS_LIFE_POINTS_VALUE_DIGITS 5

/* -------------------------------------------------------------------------- */
/* Bottom bar — money amount (e.g. "512")                                       */
/* LynJump: sub_8007CA0  |  value: gMoney                               */
/* -------------------------------------------------------------------------- */

#define STATUS_MONEY_VALUE_ROW    17
#define STATUS_MONEY_VALUE_COL     8
#define STATUS_MONEY_VALUE_DIGITS 13

/* -------------------------------------------------------------------------- */
/* Bottom bar — "domino" currency suffix (static tiles, right of money)         */
/* asm: StatusMenu loop @ 0x08007792                                            */
/* -------------------------------------------------------------------------- */

#define STATUS_MONEY_SUFFIX_ROW    18
#define STATUS_MONEY_SUFFIX_COL    22
#define STATUS_MONEY_SUFFIX_CHARS   8

/* -------------------------------------------------------------------------- */
/* Decorative accent tiles (small graphics, not the stat labels/numbers)        */
/* asm: StatusMenu loops @ 0x080076B2, 0x080076F0, 0x0800772E, 0x08007772     */
/* -------------------------------------------------------------------------- */

#define STATUS_ACCENT_GRID_A_ROW    0
#define STATUS_ACCENT_GRID_A_COL    5
#define STATUS_ACCENT_GRID_A_WIDTH 10
#define STATUS_ACCENT_GRID_B_ROW    0
#define STATUS_ACCENT_GRID_B_COL   13
#define STATUS_ACCENT_GRID_B_WIDTH 10
#define STATUS_ACCENT_GRID_C_ROW    0
#define STATUS_ACCENT_GRID_C_COL   16
#define STATUS_ACCENT_GRID_C_WIDTH 10
#define STATUS_ACCENT_LEFT_ICONS_ROW   16
#define STATUS_ACCENT_LEFT_ICONS_COL    1
#define STATUS_ACCENT_LEFT_ICONS_COUNT 10

#define STATUS_MENU_PALETTE_U16S        512

/*
 * Status screen — full LynJump replacement for StatusMenu and stat digit helpers.
 * Edit tile positions in the layout block above.
 * Label ROW/COL moves titles; split labels use row (word1) and row+1 (word2).
 */

extern u16 gUnk_8088778[][30];
extern u8 gUnk_8088288[];
extern u16 gUnk_8079424[];
extern u8 g8DF811C[];
extern u8 gUnk_8088C28[];
extern u8 gUnk_8088C50[];
extern u8 gUnk_8088C54[];
extern u8 gUnk_8088C58[];
extern u8 gUnk_8088DCC[];
extern u8 gUnk_8088E14[];
extern u32 gUnk_8E0CD14[];

extern unsigned gDuelistLevel;
extern unsigned gDeckCapacity;
extern u32 gLifePointsOutsideDuel;
extern u64 gMoney;

extern u16 gNewButtons;

void StatusMenu(void);
void sub_80079C4(void);
void sub_8007AB8(void);
void sub_8007BB0(void);
void sub_8007CA0(void);
void sub_8007DE4(void);
void sub_8007EA8(void);

#define STATUS_SBB1F_BASE 0x7C00

#define STATUS_TILE(row, col) (gBgVram.sbb1F[(row)][(col)])
#define STATUS_TILEMAP ((u16 *)&gBgVram)

static void StatusMenuWriteMapIndex(u16 mapIndex, u16 tile) {
  STATUS_TILEMAP[mapIndex] = tile;
}

#define STATUS_MONEY_LAST_DIGIT_BOTTOM_OFFSET 0xFCA8
#define STATUS_MENU_CHARBUF ((u8 *)&gBgVram + 0xC000)
#define STATUS_MENU_STR_FLAG_TALL 0x901
#define STATUS_MENU_STR_FLAG_SMALL 0x801
#define STATUS_TEXT_PALETTE_U16_OFFSET 0xF0

static void PlaceStatusMenuPalettes(void) {
  /* BG banks from the status menu asset; bank 15 keeps start-menu white text. */
  CpuCopy16(gUnk_8088288, gPaletteBuffer, STATUS_MENU_PALETTE_U16S);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[STATUS_TEXT_PALETTE_U16_OFFSET], 16);
}

static void StatusMenuClearLabelSlot(u8 row, u8 col, u8 tiles) {
  u8 i;

  for (i = 0; i < tiles; i++)
    STATUS_TILE(row, col + i) = STATUS_LABEL_PALETTE;
}

static void StatusMenuPlaceLabel(u8 row, u8 col, u8 tiles, u16 tileBase, u8 vanillaRow,
                                 u8 vanillaCol, u8 vanillaTiles) {
  u8 i;

  if (row != vanillaRow || col != vanillaCol)
    StatusMenuClearLabelSlot(vanillaRow, vanillaCol, vanillaTiles);

  for (i = 0; i < tiles; i++)
    STATUS_TILE(row, col + i) = STATUS_LABEL_PALETTE | (tileBase + i);
}

static void StatusMenuPlaceSplitLabel(u8 row, u8 col, u8 word1Tiles, u8 word2Tiles,
                                      u8 word2CharIndex, u16 tileBase, u8 vanillaRow,
                                      u8 vanillaCol, u8 vanillaTiles) {
  u8 i;
  u8 clearTiles = vanillaTiles;

  if (word1Tiles > clearTiles)
    clearTiles = word1Tiles;
  if (word2Tiles > clearTiles)
    clearTiles = word2Tiles;

  if (row != vanillaRow || col != vanillaCol) {
    StatusMenuClearLabelSlot(vanillaRow, vanillaCol, clearTiles);
    StatusMenuClearLabelSlot(vanillaRow + 1, vanillaCol, clearTiles);
  }
  StatusMenuClearLabelSlot(row, col, clearTiles);
  StatusMenuClearLabelSlot(row + 1, col, clearTiles);

  for (i = 0; i < word1Tiles; i++)
    STATUS_TILE(row, col + i) = STATUS_LABEL_PALETTE | (tileBase + i);
  for (i = 0; i < word2Tiles; i++)
    STATUS_TILE(row + 1, col + i) =
        STATUS_LABEL_PALETTE | (tileBase + word2CharIndex + i);
}

static void PlaceStatusMenuLabels(void) {
  StatusMenuPlaceLabel(STATUS_NAME_LABEL_ROW, STATUS_NAME_LABEL_COL,
                       STATUS_NAME_LABEL_TILES, STATUS_NAME_LABEL_TILE_BASE,
                       STATUS_NAME_LABEL_VANILLA_ROW, STATUS_NAME_LABEL_VANILLA_COL,
                       STATUS_NAME_LABEL_TILES);
  StatusMenuPlaceSplitLabel(STATUS_DECK_CAPACITY_LABEL_ROW, STATUS_DECK_CAPACITY_LABEL_COL,
                            STATUS_DECK_CAPACITY_WORD1_TILES,
                            STATUS_DECK_CAPACITY_WORD2_TILES,
                            STATUS_DECK_CAPACITY_WORD2_CHAR_INDEX,
                            STATUS_LABEL_TILE_BASE(STATUS_DECK_CAPACITY_LABEL_CHAR_OFFSET),
                            STATUS_DECK_CAPACITY_LABEL_VANILLA_ROW,
                            STATUS_DECK_CAPACITY_LABEL_VANILLA_COL,
                            STATUS_DECK_CAPACITY_LABEL_VANILLA_TILES);
  StatusMenuPlaceSplitLabel(STATUS_DUELIST_LEVEL_LABEL_ROW, STATUS_DUELIST_LEVEL_LABEL_COL,
                            STATUS_DUELIST_LEVEL_WORD1_TILES,
                            STATUS_DUELIST_LEVEL_WORD2_TILES,
                            STATUS_DUELIST_LEVEL_WORD2_CHAR_INDEX,
                            STATUS_LABEL_TILE_BASE(STATUS_DUELIST_LEVEL_LABEL_CHAR_OFFSET),
                            STATUS_DUELIST_LEVEL_LABEL_VANILLA_ROW,
                            STATUS_DUELIST_LEVEL_LABEL_VANILLA_COL,
                            STATUS_DUELIST_LEVEL_LABEL_VANILLA_TILES);
  StatusMenuPlaceSplitLabel(STATUS_LIFE_POINTS_LABEL_ROW, STATUS_LIFE_POINTS_LABEL_COL,
                            STATUS_LIFE_POINTS_WORD1_TILES, STATUS_LIFE_POINTS_WORD2_TILES,
                            STATUS_LIFE_POINTS_WORD2_CHAR_INDEX,
                            STATUS_LABEL_TILE_BASE(STATUS_LIFE_POINTS_LABEL_CHAR_OFFSET),
                            STATUS_LIFE_POINTS_LABEL_VANILLA_ROW,
                            STATUS_LIFE_POINTS_LABEL_VANILLA_COL,
                            STATUS_LIFE_POINTS_LABEL_VANILLA_TILES);
  StatusMenuPlaceLabel(STATUS_MONEY_LABEL_ROW, STATUS_MONEY_LABEL_COL,
                       STATUS_MONEY_LABEL_TILES, STATUS_MONEY_LABEL_TILE_BASE,
                       STATUS_MONEY_LABEL_VANILLA_ROW, STATUS_MONEY_LABEL_VANILLA_COL,
                       STATUS_MONEY_LABEL_TILES);
}

static u32 StatusMenuPow10U32(u8 digits) {
  u32 power = 1;
  u8 i;

  for (i = 1; i < digits; i++)
    power *= 10;
  return power;
}

static u64 StatusMenuPow10U64(u8 digits) {
  u64 power = 1;
  u8 i;

  for (i = 1; i < digits; i++)
    power *= 10;
  return power;
}

static u16 StatusMenuTextPalette(void) {
  return gBgVram.sbb1F[2][2] & 0xFF00;
}

static u16 StatusMenuBlankNameTile(void) {
  return gBgVram.sbb1F[1][1];
}

#define STATUS_DIGIT_BLANK_GLYPH 10

static u8 StatusMenuGlyphForDigit(u8 digit, bool8 *started) {
  if (digit != 0) {
    *started = TRUE;
    return digit;
  }
  if (*started)
    return 0;
  return STATUS_DIGIT_BLANK_GLYPH;
}

static void StatusMenuDrawDigitGlyph(u8 row, u8 col, u8 glyphIndex, u16 *bottomOut) {
  u16 topPalette = STATUS_TILE(row, col) & 0xFF00;
  u16 bottomPalette;
  u16 bottomTile;

  if (bottomOut != NULL) {
    bottomPalette = *bottomOut & 0xFF00;
    bottomTile = bottomPalette | (g8DF811C[glyphIndex] + 3);
    *bottomOut = bottomTile;
  } else {
    bottomPalette = STATUS_TILE(row + 1, col) & 0xFF00;
    STATUS_TILE(row + 1, col) = bottomPalette | (g8DF811C[glyphIndex] + 3);
  }

  STATUS_TILE(row, col) = topPalette | (g8DF811C[glyphIndex] + 1);
}

static void StatusMenuDrawU32Value(u32 value, u8 digits, u8 row, u8 col) {
  u8 i;
  bool8 started = FALSE;
  u32 divisor = StatusMenuPow10U32(digits);

  for (i = 0; i < digits; i++) {
    u8 digit = (value / divisor) % 10;
    u8 glyph = StatusMenuGlyphForDigit(digit, &started);

    StatusMenuDrawDigitGlyph(row, col + i, glyph, NULL);
    divisor /= 10;
  }
}

static void StatusMenuDrawMoneyValue(u64 value) {
  u8 i;
  bool8 started = FALSE;
  u64 divisor = StatusMenuPow10U64(STATUS_MONEY_VALUE_DIGITS);
  u16 *lastDigitBottom =
      (u16 *)((u8 *)&gBgVram + STATUS_MONEY_LAST_DIGIT_BOTTOM_OFFSET);

  for (i = 0; i < STATUS_MONEY_VALUE_DIGITS; i++) {
    u8 digit = (u8)((value / divisor) % 10);
    u8 glyph = StatusMenuGlyphForDigit(digit, &started);
    u16 *bottomOut = NULL;

    if (i == STATUS_MONEY_VALUE_DIGITS - 1 && glyph == 0 && started)
      bottomOut = lastDigitBottom;

    StatusMenuDrawDigitGlyph(STATUS_MONEY_VALUE_ROW, STATUS_MONEY_VALUE_COL + i, glyph,
                             bottomOut);
    divisor /= 10;
  }
}

static void StatusMenuDrawDuelistLevel(void) {
  StatusMenuDrawU32Value(gDuelistLevel, STATUS_DUELIST_LEVEL_VALUE_DIGITS,
                         STATUS_DUELIST_LEVEL_VALUE_ROW, STATUS_DUELIST_LEVEL_VALUE_COL);
}

static void StatusMenuDrawDeckCapacity(void) {
  StatusMenuDrawU32Value(gDeckCapacity, STATUS_DECK_CAPACITY_VALUE_DIGITS,
                         STATUS_DECK_CAPACITY_VALUE_ROW, STATUS_DECK_CAPACITY_VALUE_COL);
}

static void StatusMenuDrawLifePoints(void) {
  StatusMenuDrawU32Value(gLifePointsOutsideDuel, STATUS_LIFE_POINTS_VALUE_DIGITS,
                         STATUS_LIFE_POINTS_VALUE_ROW, STATUS_LIFE_POINTS_VALUE_COL);
}

static void StatusMenuDrawMoney(void) {
  StatusMenuDrawMoneyValue(gMoney);
}

static void PlaceStatusMenuBackground(void) {
  u8 i;

  for (i = 0; i < 20; i++)
    CpuCopy16(gUnk_8088778[i], gBgVram.sbb1F[i], 60);
}

static void PlaceStatusMenuPlayerName(u16 palette) {
  u8 i;

  for (i = 0; i < STATUS_PLAYER_NAME_LINE1_CHARS; i++)
    StatusMenuWriteMapIndex(0x7C22 + i, palette | (i + 0x19));
  for (i = 0; i < STATUS_PLAYER_NAME_LINE2_CHARS; i++)
    StatusMenuWriteMapIndex(0x7C42 + i, StatusMenuBlankNameTile());
  for (i = 0; i < STATUS_PLAYER_NAME_LINE3_CHARS; i++) {
    StatusMenuWriteMapIndex(0x7C63 + i, palette | (g8DF811C[i] + 0x5C));
    StatusMenuWriteMapIndex(0x7C83 + i, palette | (g8DF811C[i] + 0x5E));
  }
}

static void PlaceStatusMenuAccentTiles(u16 palette) {
  u8 i;

  /* Vanilla adds a flat map offset, not row * 32 + col. */
  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(STATUS_SBB1F_BASE + (i / 10 + 6) / 2 + (i % 10) + 2,
                            palette | (i + 0x20));
  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(STATUS_SBB1F_BASE + (i / 10 + 1) / 2 + (i % 10) + 0xD,
                            palette | (i + 0x34));
  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(STATUS_SBB1F_BASE + (i / 10 + 6) / 2 + (i % 10) + 0xD,
                            palette | (i + 0x48));
  for (i = 0; i < STATUS_ACCENT_LEFT_ICONS_COUNT; i++)
    StatusMenuWriteMapIndex(0x7E00 + i + 1, palette | (i + 0x6C));
}

static void PlaceStatusMenuMoneySuffix(u16 palette) {
  u8 i;

  for (i = 0; i < STATUS_MONEY_SUFFIX_CHARS; i++)
    StatusMenuWriteMapIndex(0x7E40 + i + 0x16, palette | (i + 0x76));
}

static void PlaceStatusMenuStaticTiles(void) {
  u16 palette = StatusMenuTextPalette();

  PlaceStatusMenuBackground();
  PlaceStatusMenuLabels();
  PlaceStatusMenuPlayerName(palette);
  PlaceStatusMenuAccentTiles(palette);
  PlaceStatusMenuMoneySuffix(palette);
}

static void PlaceStatusMenuLabelGfx(void) {
  u8 i;
  u8 *charBuf = STATUS_MENU_CHARBUF;
  u8 *savedName;

  PlaceStatusMenuPalettes();

  for (i = 0; i < 10; i++)
    CopyStringTilesToVRAMBuffer(charBuf + (g8DF811C[i] + 1) * 32,
                                &gUnk_8088C28[i * 4], STATUS_MENU_STR_FLAG_TALL);

  CopyStringTilesToVRAMBuffer(charBuf + 0xEC0, gUnk_8088C50, STATUS_MENU_STR_FLAG_TALL);
  CopyStringTilesToVRAMBuffer(charBuf + 0x2C0, gUnk_8088C54, STATUS_MENU_STR_FLAG_TALL);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_NAME_LABEL_CHAR_OFFSET, gUnk_8088C58,
                              STATUS_MENU_STR_FLAG_SMALL);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_DUELIST_LEVEL_LABEL_CHAR_OFFSET,
                              sStatusDuelistLevelLabel, STATUS_MENU_STR_FLAG_SMALL);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_DECK_CAPACITY_LABEL_CHAR_OFFSET,
                              sStatusDeckCapacityLabel, STATUS_MENU_STR_FLAG_SMALL);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_LIFE_POINTS_LABEL_CHAR_OFFSET,
                              sStatusLifePointsLabel, STATUS_MENU_STR_FLAG_SMALL);

  savedName = (u8 *)gUnk_8E0CD14[0];
  CopyStringTilesToVRAMBuffer(charBuf + 0xB80, savedName, STATUS_MENU_STR_FLAG_TALL);

  CopyStringTilesToVRAMBuffer(charBuf + STATUS_MONEY_LABEL_CHAR_OFFSET, gUnk_8088DCC,
                              STATUS_MENU_STR_FLAG_SMALL);
  CopyStringTilesToVRAMBuffer(charBuf + 0xEC0, gUnk_8088E14, STATUS_MENU_STR_FLAG_SMALL);
}

static void StatusMenuWaitForExit(void) {
  WaitForVBlank();
  while (!(gNewButtons & B_BUTTON))
    WaitForVBlank();
  PlayMusic(SFX_CANCEL);
}

LYN_REPLACE_CHECK(StatusMenu);
void StatusMenu__Replacement(void) {
  PlaceStatusMenuStaticTiles();
  PlaceStatusMenuLabelGfx();

  SetVBlankCallback(sub_8007EA8);
  sub_80079C4();
  sub_8007AB8();
  sub_8007BB0();
  sub_8007CA0();
  LoadCharblock3();
  LoadPalettes();
  SetVBlankCallback(sub_8007DE4);

  StatusMenuWaitForExit();
}

LYN_REPLACE_CHECK(sub_80079C4);
void sub_80079C4__Replacement(void) {
  StatusMenuDrawDuelistLevel();
}

LYN_REPLACE_CHECK(sub_8007AB8);
void sub_8007AB8__Replacement(void) {
  StatusMenuDrawDeckCapacity();
}

LYN_REPLACE_CHECK(sub_8007BB0);
void sub_8007BB0__Replacement(void) {
  StatusMenuDrawLifePoints();
}

LYN_REPLACE_CHECK(sub_8007CA0);
void sub_8007CA0__Replacement(void) {
  StatusMenuDrawMoney();
}
