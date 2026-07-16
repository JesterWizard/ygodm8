#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "gfx_reg_buffers.h"
#include "overworld.h"
#include "text.h"

#include "generated/millennium_item_assets_generated.inc"

/*
 * Status screen layout — edit constants and sSplitLabels[] below.
 * Docs: documentation/status-menu-layout.md
 * LynJump replaces StatusMenu and the four stat digit helpers at the bottom.
 */

#define STATUS_LABEL_PALETTE     0xF000
#define STATUS_LABEL_TILE_BASE(charOffset) ((u16)((charOffset) / 32))

/* Player name tile slots (asm map indices are fixed; only char counts are tunable). */
#define STATUS_PLAYER_NAME_LINE1_CHARS 7
#define STATUS_PLAYER_NAME_LINE2_CHARS 3
#define STATUS_PLAYER_NAME_LINE3_CHARS 8

#define STATUS_NAME_LABEL_ROW     2
#define STATUS_NAME_LABEL_COL     2
#define STATUS_NAME_LABEL_TILES   3
#define STATUS_NAME_LABEL_TILE_BASE 0x031
#define STATUS_NAME_LABEL_CHAR_OFFSET 0x320

#define STATUS_MONEY_LABEL_ROW    16
#define STATUS_MONEY_LABEL_COL     1
#define STATUS_MONEY_LABEL_TILES   3
#define STATUS_MONEY_LABEL_TILE_BASE 0x05E
#define STATUS_MONEY_LABEL_CHAR_OFFSET 0xD80

#define STATUS_DECK_CAPACITY_VALUE_ROW    3
#define STATUS_DECK_CAPACITY_VALUE_COL   14
#define STATUS_DECK_CAPACITY_VALUE_DIGITS 5

#define STATUS_DUELIST_LEVEL_VALUE_ROW    8
#define STATUS_DUELIST_LEVEL_VALUE_COL    3
#define STATUS_DUELIST_LEVEL_VALUE_DIGITS 4

#define STATUS_LIFE_POINTS_VALUE_ROW    8
#define STATUS_LIFE_POINTS_VALUE_COL   14
#define STATUS_LIFE_POINTS_VALUE_DIGITS 5

#define STATUS_MONEY_VALUE_ROW    17
#define STATUS_MONEY_VALUE_COL     8
#define STATUS_MONEY_VALUE_DIGITS 13

#define STATUS_MONEY_SUFFIX_CHARS 8
#define STATUS_ACCENT_LEFT_ICONS_COUNT 10

/* Horizontal millennium-item row in the clear gap between stats and money panels.
 * Tile gfx live in charblock 3 below sbb1E (BG3 map at tile index 0x180 / offset 0x3000).
 * Color+silhouette need 224 tiles → 0xA0..0x17F fits; 0x120+ silhouettes used to clobber BG3. */
#define STATUS_MILLENNIUM_ICON_ROW         10
#define STATUS_MILLENNIUM_ICON_COL_FIRST    1
#define STATUS_MILLENNIUM_ICON_COL_STEP     4
#define STATUS_MILLENNIUM_ICON_TILE_W       4
#define STATUS_MILLENNIUM_ICON_TILE_H       4
#define STATUS_MILLENNIUM_ICON_TILE_BASE 0xA0
#define STATUS_MILLENNIUM_SILHOUETTE_TILE_BASE 0x110
#define STATUS_MILLENNIUM_PAL_COLLECTED  0xD000
#define STATUS_MILLENNIUM_PAL_SILHOUETTE  0xE000
#define STATUS_MILLENNIUM_PAL_SLOT         13
#define STATUS_MILLENNIUM_PAL_SILHOUETTE_SLOT 14

static const u8 sStatusDeckCapacityLabel[] APPEND_RODATA = "Deck Capacity";
static const u8 sStatusDuelistLevelLabel[] APPEND_RODATA = "Duelist Level";
static const u8 sStatusLifePointsLabel[] APPEND_RODATA = "Life Points";

typedef struct {
  u8 row;
  u8 col;
  u8 vanillaRow;
  u8 vanillaCol;
  u8 vanillaTiles;
  u8 word1Tiles;
  u8 word2Tiles;
  u8 word2Index;
  u16 charOffset;
} StatusSplitLabel;

static const StatusSplitLabel sSplitLabels[] APPEND_RODATA = {
  { 1, 13, 2, 13, 9, 4, 8, 5, 0x680 },
  { 6,  2, 6,  2, 9, 7, 5, 8, 0x400 },
  { 6, 13, 6, 13, 8, 4, 6, 5, 0x900 },
};

typedef struct {
  u32 flag;
} StatusMillenniumItem;

/* Puzzle uses a special-case check; remaining flags map 1:1 to guardians / Mimic. */
static const StatusMillenniumItem sMillenniumItems[] APPEND_RODATA = {
  { 0 },
  { EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN3 },
  { EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN2 },
  { EVENT_FLAG_DEFEATED_MIMIC_OF_DOOM },
  { EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN5 },
  { EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4 },
  { EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN1 },
};

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

/* Middle gap is outside the blend windows (WINOUT=BG3 only), which hides BG2.
 * Keep BG2 enabled there so millennium icons (and transparent gap tiles) show. */
static void StatusMenuEnableBg2OutsideWindows(void) {
  *((vu8 *)REG_ADDR_WINOUT) = WININ_WIN0_BG2 | WININ_WIN0_BG3;
}

static void StatusMenuVBlankLoad(void) {
  sub_8007EA8();
  StatusMenuEnableBg2OutsideWindows();
}

static void StatusMenuVBlank(void) {
  sub_8007DE4();
  StatusMenuEnableBg2OutsideWindows();
}

#define STATUS_TILE(row, col) (gBgVram.sbb1F[(row)][(col)])
#define STATUS_TILEMAP ((u16 *)&gBgVram)
#define STATUS_MENU_CHARBUF ((u8 *)&gBgVram + 0xC000)
#define STATUS_MONEY_LAST_DIGIT_BOTTOM_OFFSET 0xFCA8

static void StatusMenuWriteMapIndex(u16 mapIndex, u16 tile) {
  STATUS_TILEMAP[mapIndex] = tile;
}

static u64 StatusMenuPow10(u8 digits) {
  u64 power = 1;
  u8 i;

  for (i = 1; i < digits; i++)
    power *= 10;
  return power;
}

static u16 StatusMenuTextPalette(void) {
  return gBgVram.sbb1F[2][2] & 0xFF00;
}

static void StatusMenuClearTiles(u8 row, u8 col, u8 tiles) {
  u8 i;

  for (i = 0; i < tiles; i++)
    STATUS_TILE(row, col + i) = STATUS_LABEL_PALETTE;
}

static void StatusMenuPlaceTiles(u8 row, u8 col, u8 tiles, u16 tileBase, u8 tileOffset) {
  u8 i;

  for (i = 0; i < tiles; i++)
    STATUS_TILE(row, col + i) = STATUS_LABEL_PALETTE | (tileBase + tileOffset + i);
}

static void StatusMenuPlaceSplitLabel(const StatusSplitLabel *label) {
  u8 clearTiles = label->vanillaTiles;
  u16 tileBase = STATUS_LABEL_TILE_BASE(label->charOffset);

  if (label->word1Tiles > clearTiles)
    clearTiles = label->word1Tiles;
  if (label->word2Tiles > clearTiles)
    clearTiles = label->word2Tiles;

  if (label->row != label->vanillaRow || label->col != label->vanillaCol) {
    StatusMenuClearTiles(label->vanillaRow, label->vanillaCol, clearTiles);
    StatusMenuClearTiles(label->vanillaRow + 1, label->vanillaCol, clearTiles);
  }
  StatusMenuClearTiles(label->row, label->col, clearTiles);
  StatusMenuClearTiles(label->row + 1, label->col, clearTiles);
  StatusMenuPlaceTiles(label->row, label->col, label->word1Tiles, tileBase, 0);
  StatusMenuPlaceTiles(label->row + 1, label->col, label->word2Tiles, tileBase,
                       label->word2Index);
}

static void PlaceStatusMenuLabels(void) {
  u8 i;

  StatusMenuPlaceTiles(STATUS_NAME_LABEL_ROW, STATUS_NAME_LABEL_COL,
                       STATUS_NAME_LABEL_TILES, STATUS_NAME_LABEL_TILE_BASE, 0);
  for (i = 0; i < ARRAY_COUNT(sSplitLabels); i++)
    StatusMenuPlaceSplitLabel(&sSplitLabels[i]);
  StatusMenuPlaceTiles(STATUS_MONEY_LABEL_ROW, STATUS_MONEY_LABEL_COL,
                       STATUS_MONEY_LABEL_TILES, STATUS_MONEY_LABEL_TILE_BASE, 0);
}

static u8 StatusMenuGlyphForDigit(u8 digit, bool8 *started) {
  if (digit != 0) {
    *started = TRUE;
    return digit;
  }
  if (*started)
    return 0;
  return 10;
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
  u32 divisor = (u32)StatusMenuPow10(digits);

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
  u64 divisor = StatusMenuPow10(STATUS_MONEY_VALUE_DIGITS);
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

static void PlaceStatusMenuBackground(void) {
  u8 i;

  for (i = 0; i < 20; i++)
    CpuCopy16(gUnk_8088778[i], gBgVram.sbb1F[i], 60);
}

static void PlaceStatusMenuPlayerName(u16 palette) {
  u8 i;
  u16 blank = gBgVram.sbb1F[1][1];

  for (i = 0; i < STATUS_PLAYER_NAME_LINE1_CHARS; i++)
    StatusMenuWriteMapIndex(0x7C22 + i, palette | (i + 0x19));
  for (i = 0; i < STATUS_PLAYER_NAME_LINE2_CHARS; i++)
    StatusMenuWriteMapIndex(0x7C42 + i, blank);
  for (i = 0; i < STATUS_PLAYER_NAME_LINE3_CHARS; i++) {
    StatusMenuWriteMapIndex(0x7C63 + i, palette | (g8DF811C[i] + 0x5C));
    StatusMenuWriteMapIndex(0x7C83 + i, palette | (g8DF811C[i] + 0x5E));
  }
}

static void PlaceStatusMenuAccentTiles(u16 palette) {
  u8 i;

  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(0x7C00 + (i / 10 + 6) / 2 + (i % 10) + 2, palette | (i + 0x20));
  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(0x7C00 + (i / 10 + 1) / 2 + (i % 10) + 0xD, palette | (i + 0x34));
  for (i = 0; i < 20; i++)
    StatusMenuWriteMapIndex(0x7C00 + (i / 10 + 6) / 2 + (i % 10) + 0xD, palette | (i + 0x48));
  for (i = 0; i < STATUS_ACCENT_LEFT_ICONS_COUNT; i++)
    StatusMenuWriteMapIndex(0x7E00 + i + 1, palette | (i + 0x6C));
}

static void PlaceStatusMenuMoneySuffix(u16 palette) {
  u8 i;

  for (i = 0; i < STATUS_MONEY_SUFFIX_CHARS; i++)
    StatusMenuWriteMapIndex(0x7E40 + i + 0x16, palette | (i + 0x76));
}

static bool8 StatusMenuMillenniumItemCollected(u8 index) {
  if (gRuntimeConfig.show_all_millennium_items == TRUE)
    return TRUE;
  if (index == 0)
    return !CheckFlag(EVENT_FLAG_DEFEATED_BANDIT_KEITH) ||
           CheckFlag(EVENT_FLAG_FINISHED_GAME);
  return CheckFlag(sMillenniumItems[index].flag);
}

static void StatusMenuLoadMillenniumGfx(void) {
  u8 i;
  /* BG2 charblock 3 — same block LoadCharblock3 uploads. */
  u8 *destBase = STATUS_MENU_CHARBUF;

  CpuCopy16(sMillenniumItemPalette, &gPaletteBuffer[STATUS_MILLENNIUM_PAL_SLOT * 16], 32);
  CpuCopy16(sMillenniumSilhouettePalette,
            &gPaletteBuffer[STATUS_MILLENNIUM_PAL_SILHOUETTE_SLOT * 16], 32);
  for (i = 0; i < STATUS_MILLENNIUM_ITEM_COUNT; i++) {
    u16 colorBase = STATUS_MILLENNIUM_ICON_TILE_BASE + i * STATUS_MILLENNIUM_ICON_TILE_W *
                                                            STATUS_MILLENNIUM_ICON_TILE_H;
    u16 silBase = STATUS_MILLENNIUM_SILHOUETTE_TILE_BASE + i * STATUS_MILLENNIUM_ICON_TILE_W *
                                                               STATUS_MILLENNIUM_ICON_TILE_H;

    CpuCopy32(sMillenniumItemTileSets[i], destBase + colorBase * 32,
              STATUS_MILLENNIUM_ITEM_TILE_BYTES);
    CpuCopy32(sMillenniumItemSilhouetteTileSets[i], destBase + silBase * 32,
              STATUS_MILLENNIUM_ITEM_TILE_BYTES);
  }
}

static void StatusMenuPlaceMillenniumIcon(u8 index, bool8 collected) {
  u8 col = STATUS_MILLENNIUM_ICON_COL_FIRST + index * STATUS_MILLENNIUM_ICON_COL_STEP;
  u16 tileBase =
      collected
          ? STATUS_MILLENNIUM_ICON_TILE_BASE + index * STATUS_MILLENNIUM_ICON_TILE_W *
                                                     STATUS_MILLENNIUM_ICON_TILE_H
          : STATUS_MILLENNIUM_SILHOUETTE_TILE_BASE + index * STATUS_MILLENNIUM_ICON_TILE_W *
                                                         STATUS_MILLENNIUM_ICON_TILE_H;
  u16 palette =
      collected ? STATUS_MILLENNIUM_PAL_COLLECTED : STATUS_MILLENNIUM_PAL_SILHOUETTE;
  u8 dy, dx;

  for (dy = 0; dy < STATUS_MILLENNIUM_ICON_TILE_H; dy++) {
    for (dx = 0; dx < STATUS_MILLENNIUM_ICON_TILE_W; dx++)
      STATUS_TILE(STATUS_MILLENNIUM_ICON_ROW + dy, col + dx) =
          palette | (tileBase + dy * STATUS_MILLENNIUM_ICON_TILE_W + dx);
  }
}

static void PlaceStatusMenuMillenniumTracker(void) {
  u8 i;

  StatusMenuLoadMillenniumGfx();
  for (i = 0; i < STATUS_MILLENNIUM_ITEM_COUNT; i++)
    StatusMenuPlaceMillenniumIcon(i, StatusMenuMillenniumItemCollected(i));
}

static void PlaceStatusMenuLabelGfx(void) {
  u8 i;
  u8 *charBuf = STATUS_MENU_CHARBUF;

  CpuCopy16(gUnk_8088288, gPaletteBuffer, 512);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 16);

  for (i = 0; i < 10; i++)
    CopyStringTilesToVRAMBuffer(charBuf + (g8DF811C[i] + 1) * 32,
                                &gUnk_8088C28[i * 4], 0x901);

  CopyStringTilesToVRAMBuffer(charBuf + 0xEC0, gUnk_8088C50, 0x901);
  CopyStringTilesToVRAMBuffer(charBuf + 0x2C0, gUnk_8088C54, 0x901);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_NAME_LABEL_CHAR_OFFSET, gUnk_8088C58, 0x801);
  CopyStringTilesToVRAMBuffer(charBuf + 0xB80, (u8 *)gUnk_8E0CD14[0], 0x901);
  CopyStringTilesToVRAMBuffer(charBuf + STATUS_MONEY_LABEL_CHAR_OFFSET, gUnk_8088DCC, 0x801);
  CopyStringTilesToVRAMBuffer(charBuf + 0xEC0, gUnk_8088E14, 0x801);
  CopyStringTilesToVRAMBuffer(charBuf + 0x680, sStatusDeckCapacityLabel, 0x801);
  CopyStringTilesToVRAMBuffer(charBuf + 0x400, sStatusDuelistLevelLabel, 0x801);
  CopyStringTilesToVRAMBuffer(charBuf + 0x900, sStatusLifePointsLabel, 0x801);
}

LYN_REPLACE_CHECK(StatusMenu);
void StatusMenu__Replacement(void) {
  u16 palette = StatusMenuTextPalette();

  PlaceStatusMenuBackground();
  PlaceStatusMenuLabels();
  PlaceStatusMenuPlayerName(palette);
  PlaceStatusMenuAccentTiles(palette);
  PlaceStatusMenuMoneySuffix(palette);
  PlaceStatusMenuLabelGfx();
  PlaceStatusMenuMillenniumTracker();

  SetVBlankCallback(StatusMenuVBlankLoad);
  StatusMenuDrawU32Value(gDuelistLevel, STATUS_DUELIST_LEVEL_VALUE_DIGITS,
                         STATUS_DUELIST_LEVEL_VALUE_ROW, STATUS_DUELIST_LEVEL_VALUE_COL);
  StatusMenuDrawU32Value(gDeckCapacity, STATUS_DECK_CAPACITY_VALUE_DIGITS,
                         STATUS_DECK_CAPACITY_VALUE_ROW, STATUS_DECK_CAPACITY_VALUE_COL);
  StatusMenuDrawU32Value(gLifePointsOutsideDuel, STATUS_LIFE_POINTS_VALUE_DIGITS,
                         STATUS_LIFE_POINTS_VALUE_ROW, STATUS_LIFE_POINTS_VALUE_COL);
  StatusMenuDrawMoneyValue(gMoney);
  LoadCharblock3();
  LoadPalettes();
  SetVBlankCallback(StatusMenuVBlank);

  WaitForVBlank();
  while (!(gNewButtons & B_BUTTON))
    WaitForVBlank();
  PlayMusic(SFX_CANCEL);
}

LYN_REPLACE_CHECK(sub_80079C4);
void sub_80079C4__Replacement(void) {
  StatusMenuDrawU32Value(gDuelistLevel, STATUS_DUELIST_LEVEL_VALUE_DIGITS,
                         STATUS_DUELIST_LEVEL_VALUE_ROW, STATUS_DUELIST_LEVEL_VALUE_COL);
}

LYN_REPLACE_CHECK(sub_8007AB8);
void sub_8007AB8__Replacement(void) {
  StatusMenuDrawU32Value(gDeckCapacity, STATUS_DECK_CAPACITY_VALUE_DIGITS,
                         STATUS_DECK_CAPACITY_VALUE_ROW, STATUS_DECK_CAPACITY_VALUE_COL);
}

LYN_REPLACE_CHECK(sub_8007BB0);
void sub_8007BB0__Replacement(void) {
  StatusMenuDrawU32Value(gLifePointsOutsideDuel, STATUS_LIFE_POINTS_VALUE_DIGITS,
                         STATUS_LIFE_POINTS_VALUE_ROW, STATUS_LIFE_POINTS_VALUE_COL);
}

LYN_REPLACE_CHECK(sub_8007CA0);
void sub_8007CA0__Replacement(void) {
  StatusMenuDrawMoneyValue(gMoney);
}
