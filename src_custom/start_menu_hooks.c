#include "global.h"
#include "configs/runtime.h"
#include "player_decks.h"
#include "start_menu.h"

extern unsigned char gStartMenuBgTiles[];
extern unsigned char gStartMenuCursorTiles[];
extern unsigned short gStartMenuBgPalette[];
extern unsigned short gStartMenuCursorPalette[];
extern unsigned short gUnk_8079424[];
extern unsigned short gUnk_8079444[][30];
extern unsigned short gUnk_80798F4[][30];
extern unsigned short gUnk_8079CB4[][30];
extern unsigned short gUnk_807A164[][30];
extern unsigned char gText_DeckMustHave40Cards[];
extern unsigned char gText_CardCostTotal[];
extern unsigned char sText_Status[];
extern unsigned char sText_Trunk[];
extern unsigned char sText_Deck[];

extern u16 gOamBuffer[];
extern u16 gNewButtons;

void InitTrunkData(void);
void InitDeckData(void);
void StatusMenu(void);
void TrunkMenuMain(void);
bool8 IsPlayerDeckFull(void);
bool32 IsCostWithinCapacity(void);
u32 IsPlayerDeckNonempty(void);
void DeckMenuMain(void);
void ClearGraphicsBuffers(void);

static const u8 sText_Deck1[] APPEND_TEXT = "Deck 1";
static const u8 sText_Deck2[] APPEND_TEXT = "Deck 2";
static const u8 sText_Deck3[] APPEND_TEXT = "Deck 3";

#define VANILLA_THUMB_CALL(addr) ((void (*)(void))((addr) | 1))

/* Start-menu layout in 8x8 tiles (hardware uses pixels = tiles * 8). */

/* Window 0 clip: REG_WIN0V = (top_px << 8) | bottom_px (matches vanilla 0x2878). */
#define START_MENU_WIN0_TOP_TILES              3
#define START_MENU_WIN0_BOTTOM_TILES_VANILLA  15
#define START_MENU_WIN0_BOTTOM_TILES_EXTENDED 18

#define START_MENU_WIN0V_FROM_TILES(topTiles, bottomTiles) \
  ((((topTiles) * 8) << 8) | ((bottomTiles) * 8))

#define START_MENU_WIN0V_VANILLA \
  START_MENU_WIN0V_FROM_TILES(START_MENU_WIN0_TOP_TILES, START_MENU_WIN0_BOTTOM_TILES_VANILLA)
#define START_MENU_WIN0V_EXTENDED \
  START_MENU_WIN0V_FROM_TILES(START_MENU_WIN0_TOP_TILES, START_MENU_WIN0_BOTTOM_TILES_EXTENDED)

/*
 * BG2 scroll (signed tiles). Increasing this nudge moves text up on screen.
 * Vanilla -7; +4 tiles nudge lifts the five-line menu by whole BG2 tiles.
 */
#define START_MENU_BG2_TEXT_NUDGE_TILES 1
#define START_MENU_BG2_SCROLL_TILES_VANILLA   (-7)
#define START_MENU_BG2_SCROLL_TILES_EXTENDED \
  (START_MENU_BG2_SCROLL_TILES_VANILLA + START_MENU_BG2_TEXT_NUDGE_TILES)

#define START_MENU_BG2VOFS_FROM_TILES(scrollTiles) ((u16)(s16)((scrollTiles) * 8))

#define START_MENU_BG2VOFS_VANILLA \
  START_MENU_BG2VOFS_FROM_TILES(START_MENU_BG2_SCROLL_TILES_VANILLA)
#define START_MENU_BG2VOFS_EXTENDED \
  START_MENU_BG2VOFS_FROM_TILES(START_MENU_BG2_SCROLL_TILES_EXTENDED)

/* Millennium Eye cursor Y tracks the BG2 text scroll, so tile nudges stay aligned. */
#define START_MENU_CURSOR_Y_TILES (0 - START_MENU_BG2_SCROLL_TILES_EXTENDED)

/* BG2 text tilemap rows (2 tile rows per menu line). */
#define START_MENU_TEXT_ROW_DECK1 4
#define START_MENU_TEXT_ROW_DECK2 6
#define START_MENU_TEXT_ROW_DECK3 8

#define START_MENU_DECK_LABEL_CHARS 6
#define START_MENU_TEXT_PALETTE 0xF000
#define START_MENU_ACTIVE_TEXT_PALETTE 0xE000
#define START_MENU_ACTIVE_BG_PALETTE 0xE0
#define START_MENU_ACTIVE_YELLOW_COLOR 0x27BF
#define START_MENU_TILE_DECK1 0x00A9
#define START_MENU_TILE_DECK2 0x00C1
#define START_MENU_TILE_DECK3 0x00D9

#define START_MENU_TEXT_VRAM_DECK1 0x5520
#define START_MENU_TEXT_VRAM_DECK2 0x5820
#define START_MENU_TEXT_VRAM_DECK3 0x5B20

static void LoadStartMenuGraphicsVanilla(void);
static void LoadStartMenuGraphicsMultiDeck(void);
static void InitStartMenuDataVanilla(void);
static void InitStartMenuDataMultiDeck(void);
static void ExtendStartMenuPanelMaps(void);
static void WriteStartMenuTextLineMap(u8 tileRow, u16 firstTile, u8 charCount);
static void SetStartMenuTextLinePalette(u8 tileRow, u8 charCount, u16 palette);
static void UpdateActiveDeckTextColor(void);
static void StartMenuVBlank(void);
static void StartMenuVBlankAfterMessage(void);
static void UpdateCursorPositionVanilla(u8 cursorPos);
static void UpdateCursorPositionMultiDeck(u8 cursorPos);
static void RestoreStartMenuAfterSubmenu(void);
static void SelectActiveDeckFromStartMenu(u8 deckIndex);
static void HandleDeckSelection(u8 deckIndex);

void sub_8005C38(void);
void sub_8005C54(void);

static void LoadStartMenuGraphicsVanilla(void) {
  u8 i;

  LZ77UnCompWram((const u32 *)gStartMenuCursorTiles, gBgVram.cbb4);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_80798F4[i], gBgVram.sbb1F[i], 60);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_8079CB4[i], gBgVram.sbb1D[i], 60);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_807A164[i], gBgVram.sbb1C[i], 60);
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[32], gText_DeckMustHave40Cards, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x1020], gText_CardCostTotal, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x5020], sText_Status, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x52A0], sText_Trunk, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x5520], sText_Deck, 0x901);
}

static void LoadStartMenuGraphicsMultiDeck(void) {
  u8 i;

  LZ77UnCompWram((const u32 *)gStartMenuCursorTiles, gBgVram.cbb4);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_80798F4[i], gBgVram.sbb1F[i], 60);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_8079CB4[i], gBgVram.sbb1D[i], 60);
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_807A164[i], gBgVram.sbb1C[i], 60);
  CpuCopy16(gStartMenuBgPalette, gPaletteBuffer, 32);
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[START_MENU_ACTIVE_BG_PALETTE], 32);
  gPaletteBuffer[START_MENU_ACTIVE_BG_PALETTE + 1] = START_MENU_ACTIVE_YELLOW_COLOR;
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[32], gText_DeckMustHave40Cards, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x1020], gText_CardCostTotal, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x5020], sText_Status, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[0x52A0], sText_Trunk, 0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[START_MENU_TEXT_VRAM_DECK1], sText_Deck1,
                              0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[START_MENU_TEXT_VRAM_DECK2], sText_Deck2,
                              0x901);
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb2[START_MENU_TEXT_VRAM_DECK3], sText_Deck3,
                              0x901);
  WriteStartMenuTextLineMap(START_MENU_TEXT_ROW_DECK1, START_MENU_TILE_DECK1,
                            START_MENU_DECK_LABEL_CHARS);
  WriteStartMenuTextLineMap(START_MENU_TEXT_ROW_DECK2, START_MENU_TILE_DECK2,
                            START_MENU_DECK_LABEL_CHARS);
  WriteStartMenuTextLineMap(START_MENU_TEXT_ROW_DECK3, START_MENU_TILE_DECK3,
                            START_MENU_DECK_LABEL_CHARS);
  UpdateActiveDeckTextColor();
}

static void LoadStartMenuGraphicsFull(void) {
  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  LoadVRAM();
  DisableDisplay();
  LZ77UnCompWram((const u32 *)gStartMenuBgTiles, gBgVram.cbb0);

  if (PlayerDecks_IsEnabled() == TRUE)
    LoadStartMenuGraphicsMultiDeck();
  else
    LoadStartMenuGraphicsVanilla();
}

static void InitStartMenuDataVanilla(void) {
  u8 i;

  LoadStartMenuGraphicsFull();
  for (i = 0; i < 20; i++)
    DmaCopy16(3, gUnk_8079444[i], gBgVram.sbb1E[i], 60);
  if (PlayerDecks_IsEnabled() == TRUE)
    ExtendStartMenuPanelMaps();
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xF0], 32);
  if (PlayerDecks_IsEnabled() == TRUE)
    SetVBlankCallback(StartMenuVBlank);
  else
    SetVBlankCallback((void (*)(void))(0x08005C39));
  LoadBgVRAM();
  LoadCharblock4();
  LoadPalettes();
  WaitForVBlank();
  InitTrunkData();
  InitDeckData();
}

static void CopyStartMenuTilemapRow(u16 *destRow, const u16 *srcRow) {
  CpuCopy16(srcRow, destRow, 60);
}

static void WriteStartMenuTextLineMap(u8 tileRow, u16 firstTile, u8 charCount) {
  u8 i;
  u16 *top = gBgVram.sbb1F[tileRow];
  u16 *bottom = gBgVram.sbb1F[tileRow + 1];

  for (i = 0; i < 30; i++) {
    top[i] = START_MENU_TEXT_PALETTE;
    bottom[i] = START_MENU_TEXT_PALETTE;
  }

  for (i = 0; i < charCount; i++) {
    u16 tile = firstTile + i * 4;
    top[i * 2] = START_MENU_TEXT_PALETTE | tile;
    top[i * 2 + 1] = START_MENU_TEXT_PALETTE | (tile + 1);
    bottom[i * 2] = START_MENU_TEXT_PALETTE | (tile + 2);
    bottom[i * 2 + 1] = START_MENU_TEXT_PALETTE | (tile + 3);
  }
}

static void SetStartMenuTextLinePalette(u8 tileRow, u8 charCount, u16 palette) {
  u8 i;
  u16 *top = gBgVram.sbb1F[tileRow];
  u16 *bottom = gBgVram.sbb1F[tileRow + 1];

  for (i = 0; i < charCount * 2; i++) {
    top[i] = (top[i] & 0x0FFF) | palette;
    bottom[i] = (bottom[i] & 0x0FFF) | palette;
  }
}

static void UpdateActiveDeckTextColor(void) {
  u8 activeDeck = PlayerDecks_GetActiveIndex();

  SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK1, START_MENU_DECK_LABEL_CHARS,
                              START_MENU_TEXT_PALETTE);
  SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK2, START_MENU_DECK_LABEL_CHARS,
                              START_MENU_TEXT_PALETTE);
  SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK3, START_MENU_DECK_LABEL_CHARS,
                              START_MENU_TEXT_PALETTE);

  switch (activeDeck) {
  case 1:
    SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK1, START_MENU_DECK_LABEL_CHARS,
                                START_MENU_ACTIVE_TEXT_PALETTE);
    break;
  case 2:
    SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK2, START_MENU_DECK_LABEL_CHARS,
                                START_MENU_ACTIVE_TEXT_PALETTE);
    break;
  default:
    SetStartMenuTextLinePalette(START_MENU_TEXT_ROW_DECK3, START_MENU_DECK_LABEL_CHARS,
                                START_MENU_ACTIVE_TEXT_PALETTE);
    break;
  }
}

static void ExtendStartMenuPanelMaps(void) {
  u8 r;

  /* Inner frame on BG1/BG2: vanilla border is tile rows 8-11; stretch to 8-15. */
  for (r = 12; r <= 15; r++) {
    u8 srcRow = 10 + ((r - 12) & 1);

    CopyStartMenuTilemapRow(gBgVram.sbb1D[r], gUnk_8079CB4[srcRow]);
    CopyStartMenuTilemapRow(gBgVram.sbb1C[r], gUnk_807A164[srcRow]);
  }

  /* Dim panel on BG3: add two rows below the vanilla box bottom. */
  CopyStartMenuTilemapRow(gBgVram.sbb1E[16], gUnk_8079444[13]);
  CopyStartMenuTilemapRow(gBgVram.sbb1E[17], gUnk_8079444[14]);
}

static void ApplyStartMenuWindowHeight(void) {
  if (PlayerDecks_IsEnabled() == TRUE) {
    REG_WIN0V = START_MENU_WIN0V_EXTENDED;
    gBG2VOFS = START_MENU_BG2VOFS_EXTENDED;
  } else {
    REG_WIN0V = START_MENU_WIN0V_VANILLA;
    gBG2VOFS = START_MENU_BG2VOFS_VANILLA;
  }
}

static void StartMenuVBlank(void) {
  *((vu8 *)REG_ADDR_WININ) = 0x3C;
  *((vu8 *)REG_ADDR_WINOUT) = 8;
  VANILLA_THUMB_CALL(0x080059D4)();
  ApplyStartMenuWindowHeight();
  LoadBgOffsets();
}

static void StartMenuVBlankAfterMessage(void) {
  VANILLA_THUMB_CALL(0x080059D4)();
  ApplyStartMenuWindowHeight();
  LoadBgOffsets();
}

static void InitStartMenuDataMultiDeck(void) {
  InitStartMenuDataVanilla();
}

static void UpdateCursorPositionVanilla(u8 cursorPos) {
  u32 *oam = (u32 *)&gOamBuffer;

  oam[0] = (cursorPos << 4) + 56 | 0x40400000;
  oam[1] = 0x800;
}

static void UpdateCursorPositionMultiDeck(u8 cursorPos) {
  u32 *oam = (u32 *)&gOamBuffer;

  oam[0] = (cursorPos << 4) + (START_MENU_CURSOR_Y_TILES * 8) | 0x40400000;
  oam[1] = 0x800;
}

static void DisplayIncompleteDeckMessageVanilla(void) {
  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON;
  LoadBgOffsets();
  VANILLA_THUMB_CALL(0x08005CB8)();
}

static void DisplayCostMessageVanilla(void) {
  REG_DISPCNT = DISPCNT_BG0_ON | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON;
  LoadBgOffsets();
  VANILLA_THUMB_CALL(0x08005CB8)();
}

static void StartMenuMainVanilla(void) {
  u8 cursorState = 0;

  while (1) {
    if (gNewButtons & B_BUTTON) {
      if (!IsPlayerDeckFull()) {
        PlayMusic(SFX_FORBIDDEN);
        DisplayIncompleteDeckMessageVanilla();
        VANILLA_THUMB_CALL(0x08005BE0)();
      } else if (IsCostWithinCapacity()) {
        if (IsPlayerDeckFull() != TRUE || IsCostWithinCapacity() != TRUE)
          goto here;
        else
          break;
      } else {
        PlayMusic(SFX_FORBIDDEN);
        DisplayCostMessageVanilla();
        VANILLA_THUMB_CALL(0x08005BE0)();
      }
    }
  here:
    if (gNewButtons & DPAD_UP && cursorState != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursorState--;
    }
    if (gNewButtons & DPAD_DOWN && cursorState < 2) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursorState++;
    }
    switch (cursorState) {
    case 0:
      if (gNewButtons & A_BUTTON) {
        PlayMusic(SFX_SELECT);
        StatusMenu();
        VANILLA_THUMB_CALL(0x08005BE0)();
      }
      break;
    case 1:
      if (gNewButtons & A_BUTTON) {
        PlayMusic(SFX_SELECT);
        TrunkMenuMain();
        InitStartMenuDataVanilla();
      }
      break;
    case 2:
      if (gNewButtons & A_BUTTON) {
        if (IsPlayerDeckNonempty() == 1) {
          PlayMusic(SFX_SELECT);
          DeckMenuMain();
          LoadStartMenuGraphicsVanilla();
        } else {
          PlayMusic(SFX_FORBIDDEN);
        }
      }
      break;
    }
    UpdateCursorPositionVanilla(cursorState);
    LoadOam();
    WaitForVBlank();
  }
  PlayMusic(SFX_CANCEL);
  DisableDisplay();
}

static void OpenDeckEditor(u8 deckIndex) {
  PlayerDecks_SetActiveAndLoad(deckIndex);
  DeckMenuMain();
  PlayerDecks_FlushActive();
  if (PlayerDecks_IsEnabled() == TRUE)
    InitStartMenuDataMultiDeck();
  else
    InitStartMenuDataVanilla();
}

static void RestoreStartMenuAfterSubmenu(void) {
  if (PlayerDecks_IsEnabled() == TRUE)
    InitStartMenuDataMultiDeck();
  else
    VANILLA_THUMB_CALL(0x08005BE0)();
}

static void SelectActiveDeckFromStartMenu(u8 deckIndex) {
  PlayerDecks_SetActiveAndLoad(deckIndex);
  UpdateActiveDeckTextColor();
  LoadBgVRAM();
}

static void HandleDeckSelection(u8 deckIndex) {
  if (PlayerDecks_GetActiveIndex() != deckIndex) {
    PlayMusic(SFX_SELECT);
    SelectActiveDeckFromStartMenu(deckIndex);
  } else if (IsPlayerDeckNonempty() == 1) {
    PlayMusic(SFX_SELECT);
    OpenDeckEditor(deckIndex);
  } else {
    PlayMusic(SFX_FORBIDDEN);
  }
}

static void StartMenuMainMultiDeck(void) {
  u8 cursorState = 0;

  while (1) {
    if (gNewButtons & B_BUTTON) {
      if (!IsPlayerDeckFull()) {
        PlayMusic(SFX_FORBIDDEN);
        DisplayIncompleteDeckMessageVanilla();
        InitStartMenuDataMultiDeck();
      } else if (IsCostWithinCapacity()) {
        if (IsPlayerDeckFull() != TRUE || IsCostWithinCapacity() != TRUE)
          goto here;
        else
          break;
      } else {
        PlayMusic(SFX_FORBIDDEN);
        DisplayCostMessageVanilla();
        InitStartMenuDataMultiDeck();
      }
    }
  here:
    if (gNewButtons & DPAD_UP && cursorState != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursorState--;
    }
    if (gNewButtons & DPAD_DOWN && cursorState < 4) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursorState++;
    }
    switch (cursorState) {
    case 0:
      if (gNewButtons & A_BUTTON) {
        PlayMusic(SFX_SELECT);
        StatusMenu();
        RestoreStartMenuAfterSubmenu();
      }
      break;
    case 1:
      if (gNewButtons & A_BUTTON) {
        PlayMusic(SFX_SELECT);
        TrunkMenuMain();
        PlayerDecks_FlushActive();
        InitStartMenuDataMultiDeck();
      }
      break;
    case 2:
      if (gNewButtons & A_BUTTON) {
        HandleDeckSelection(PLAYER_DECK_INDEX_MIN);
      }
      break;
    case 3:
      if (gNewButtons & A_BUTTON) {
        HandleDeckSelection(2);
      }
      break;
    case 4:
      if (gNewButtons & A_BUTTON) {
        HandleDeckSelection(PLAYER_DECK_INDEX_MAX);
      }
      break;
    }
    UpdateCursorPositionMultiDeck(cursorState);
    LoadOam();
    WaitForVBlank();
  }
  PlayMusic(SFX_CANCEL);
  DisableDisplay();
}

static void StartMenuMain__Impl(void) {
  if (PlayerDecks_IsEnabled() == TRUE)
    StartMenuMainMultiDeck();
  else
    StartMenuMainVanilla();
}

LYN_REPLACE_CHECK(InitStartMenu);
void InitStartMenu__Replacement(void) {
  FadeOutMusic(1);

  if (PlayerDecks_IsEnabled() == TRUE)
    InitStartMenuDataMultiDeck();
  else
    InitStartMenuDataVanilla();

  PlayMusic(MUSIC_DECK_ADJUSTMENT_MENU);
  StartMenuMain__Impl();
  FadeOutMusic(1);
}

LYN_REPLACE_CHECK(sub_8005C38);
void sub_8005C38__Replacement(void) {
  StartMenuVBlank();
}

LYN_REPLACE_CHECK(sub_8005C54);
void sub_8005C54__Replacement(void) {
  StartMenuVBlankAfterMessage();
}

LYN_REPLACE_CHECK(InitStartMenuFromScript);
void InitStartMenuFromScript__Replacement(void) {
  if (PlayerDecks_IsEnabled() == TRUE)
    InitStartMenuDataMultiDeck();
  else
    InitStartMenuDataVanilla();

  StartMenuMain__Impl();
}
