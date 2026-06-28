#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"
#include "match_setter.h"
#include "debug_save_anywhere.h"
#include "text.h"

extern const u16 gOverworldEntityPalettes[];

/* ponytail: sidebar art replaces start-menu bg.  Cursor tiles still come from
 * the vanilla start menu (small OBJ sprite) — not worth a custom cursor.
 * ponytail: R button toggles BG0 (text) visibility in the root menu. */
extern u8 gStartMenuBgTiles[];
extern u8 gStartMenuCursorTiles[];
extern u16 gStartMenuBgPalette[];
extern u16 gStartMenuCursorPalette[];
extern u16 gUnk_8079444[][30];
extern u16 gUnk_80798F4[][30];
extern u16 gUnk_8079CB4[][30];
extern u16 gUnk_807A164[][30];

/* ponytail: no sidebar art — BG1 shows solid black instead. */

/* Save area for OBJ tiles (cbb5 is unused — sidebar OBJ tiles were removed). */
#define DEBUG_OBJ_SAVE_SIZE   0x2000
#define DEBUG_OBJ_SAVE_ADDR   ((void *)0x06010000)
#define DEBUG_OBJ_SAVE_BUF    (gBgVram.cbb5)

static const u8 sText_RootMusic[] APPEND_RODATA        = "Music";
static const u8 sText_RootPortrait[] APPEND_RODATA     = "Portrait";
static const u8 sText_RootSprite[] APPEND_RODATA       = "Sprite";
static const u8 sText_RootReaction[] APPEND_RODATA     = "Reaction";
static const u8 sText_RootGraphic[] APPEND_RODATA      = "Graphic";
static const u8 sText_RootVoice[] APPEND_RODATA        = "Voice";
static const u8 sText_RootMatchSetter[] APPEND_RODATA  = "Match";
static const u8 sText_RootMap[] APPEND_RODATA          = "Map";
static const u8 sText_RootScene[] APPEND_RODATA        = "Scene";
static const u8 sText_RootAiMode[] APPEND_RODATA       = "AI Mode";
static const u8 sText_RootRuleset[] APPEND_RODATA      = "Ruleset";
static const u8 sText_RootDeckPreset[] APPEND_RODATA   = "Decks";
static const u8 sText_RootSaveAnywhere[] APPEND_RODATA = "Save";

/* Section titles — 16 chars each, centered. */
static const u8 sText_SectionMusic[] APPEND_RODATA    = "  Music Player  ";
static const u8 sText_SectionPortrait[] APPEND_RODATA = " Portrait Viewer";
static const u8 sText_SectionSprite[] APPEND_RODATA   = " Sprite Viewer  ";
static const u8 sText_SectionReaction[] APPEND_RODATA = "Reaction Viewer ";
static const u8 sText_SectionGraphic[] APPEND_RODATA  = " Graphic Viewer ";
static const u8 sText_SectionVoice[] APPEND_RODATA    = "  Voice Player  ";
static const u8 sText_SectionMatch[] APPEND_RODATA    = " Match Setter   ";
static const u8 sText_SectionAiMode[] APPEND_RODATA   = "   AI Mode      ";
static const u8 sText_SectionRuleset[] APPEND_RODATA  = "   Ruleset      ";
static const u8 sText_SectionMap[] APPEND_RODATA      = "  Map Teleport  ";
static const u8 sText_SectionScene[] APPEND_RODATA    = " Scene Viewer   ";
static const u8 sText_SectionDecks[] APPEND_RODATA    = "  Deck Presets  ";

static const u8 *const sRootLabels[] APPEND_RODATA = {
    sText_RootMusic,
    sText_RootPortrait,
    sText_RootSprite,
    sText_RootReaction,
    sText_RootGraphic,
    sText_RootVoice,
    sText_RootMatchSetter,
    sText_RootMap,
    sText_RootScene,
    sText_RootAiMode,
    sText_RootRuleset,
    sText_RootDeckPreset,
    sText_RootSaveAnywhere,
};
const u8 gDebugMenuBlankLine[] APPEND_RODATA = "          ";

extern u16 gUnk_8079424[];
extern u16 gOamBuffer[];
extern u16 gNewButtons;
extern u16 gPressedButtons;
extern u16 gRepeatedOrNewButtons;
extern vu8 gRepeatedButtonsCounter;
extern u8 gInputRepeatTimer;

void InitButtonMaps(void);
void LoadBgVRAM(void);
void LoadCharblock4(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void LoadBgOffsets(void);
void LoadOam(void);
void SetVBlankCallback(void (*)(void));

static inline void CallThumbVoid(u32 addr) {
  ((void (*)(void))(addr | 1))();
}

/* ------------------------------------------------------------------ */
/*  VBlank — overworld renders first, then debug menu overrides        */
/*  Sidebar = OBJ sprites, text = BG0, BG2/BG3 left to overworld.     */
/*  BG1 = debug menu's solid black backdrop.                           */
/* ------------------------------------------------------------------ */

void DebugMenuLoadCursorObjTiles(void) {
  CpuFastCopy(DEBUG_OBJ_SAVE_ADDR, DEBUG_OBJ_SAVE_BUF, DEBUG_OBJ_SAVE_SIZE);
  CpuFill16(0, DEBUG_OBJ_SAVE_ADDR, DEBUG_OBJ_SAVE_SIZE);
  CpuFill16(0, gBgVram.cbb4, DEBUG_OBJ_SAVE_SIZE);
  LZ77UnCompWram(gStartMenuCursorTiles, gBgVram.cbb4);
  {
    const u32 *src3 = (const u32 *)(gBgVram.cbb4 + 0x060);
    const u32 *src4 = (const u32 *)(gBgVram.cbb4 + 0x080);
    u32      *dst3 = (u32       *)(gBgVram.cbb4 + 0x2400);
    u32      *dst4 = (u32       *)(gBgVram.cbb4 + 0x2420);
    u8 i;

    for (i = 0; i < 8; i++) {
      dst3[i] = src3[i];
      dst4[i] = src4[i];
    }
  }
}

static void DebugMenuSetupTextPalettes(void) {
  gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16 + DEBUG_BG1_TEXT_PAL_INDEX] = gUnk_8079424[1];
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16, 32);
  gPaletteBuffer[DEBUG_MENU_HIGHLIGHT_PAL_BANK * 16 + DEBUG_BG1_TEXT_PAL_INDEX] = 0x03FF;
}

static void DebugMenuVBlank(void) {
  ((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1))();
  {
    /* ponytail: don't force BG3_ON — preserves overworld's BG3 state.
     * Same for BG2 (roof layer). */
    /* BG1 = solid black (charbase 0, screenbase 0, tile 0 blanked). */
    REG_DISPCNT = DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON;
    /* ponytail: preserve overworld's BG2 (roof) and BG3. */
    if (REG_DISPCNT & DISPCNT_BG2_ON)
      REG_DISPCNT |= DISPCNT_BG2_ON;
    if (REG_DISPCNT & DISPCNT_BG3_ON)
      REG_DISPCNT |= DISPCNT_BG3_ON;
  }
  REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_16COLOR | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(DEBUG_BG0_SBB);
  REG_BG0HOFS = 0xFFF8;  REG_BG0VOFS = 0;
  REG_BG1CNT = BGCNT_PRIORITY(2) | BGCNT_16COLOR | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(0);
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;
  /* ponytail: re-apply yellow highlight palette every frame so the
   * overworld VBlank (which doesn't touch this bank) can't stale it. */
  *((vu16 *)0x05000000 + DEBUG_MENU_HIGHLIGHT_PAL_BANK * 16 + DEBUG_BG1_TEXT_PAL_INDEX) = 0x03FF;
  /* Re-apply cursor palette entry 1 (main eye color) — sub-viewers may clobber it. */
  *((vu16 *)0x050003E2) = gStartMenuCursorPalette[1];
}

void DebugMenuVBlankNoWin(void) {
  ((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1))();
}

void DebugMenuWaitVBlank(void) {
  SetVBlankCallback(DebugMenuVBlank);
  WaitForVBlank();
}

/* ------------------------------------------------------------------ */
/*  Text rendering — small overworld font in cbb1                     */
/* ------------------------------------------------------------------ */

void DebugMenuCopyLine(u8 row, const u8 *text) {
  u8 i, j;
  u8 *glyphDest = (u8 *)gBgVram.cbb1 + (DEBUG_BG1_TEXT_TILE_BASE + row * DEBUG_CHARS) * 32;
  u16 tileBase = DEBUG_BG1_TEXT_TILE_BASE + row * DEBUG_CHARS;
  u16 palMask = DEBUG_BG1_TEXT_PAL_BANK << 12;

  CopyStringTilesToVRAMBuffer(glyphDest, text, 0x001);

  /* Shift font pixel index 1 → DEBUG_BG1_TEXT_PAL_INDEX so font
   * uses slot 9 in the font palette bank (bank 0) instead of slot 1. */
  for (j = 0; j < DEBUG_CHARS; j++) {
    u8 *tile = (u8 *)gBgVram.cbb1 + (tileBase + j) * 32;
    for (i = 0; i < 32; i++) {
      u8 p = tile[i];
      u8 lo = p & 0xF;
      u8 hi = p >> 4;
      if (lo == 1) lo = DEBUG_BG1_TEXT_PAL_INDEX;
      if (hi == 1) hi = DEBUG_BG1_TEXT_PAL_INDEX;
      tile[i] = lo | (hi << 4);
    }
  }

  for (i = 0; i < DEBUG_CHARS; i++) {
    if (text[i] == '\0')
      break;
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] =
        palMask | (tileBase + i);
  }
  for (; i < DEBUG_CHARS; i++)
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] =
        palMask | 0;
}

void DebugMenuRestoreTextPalettes(void) {
  gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16 + DEBUG_BG1_TEXT_PAL_INDEX] = gUnk_8079424[1];
}

void DebugMenuSetLinePalette(u8 row, u8 paletteNum) {
  u8 i;
  u16 palMask = (paletteNum & 0xF) << 12;

  gPaletteBuffer[(paletteNum & 0xF) * 16 + DEBUG_BG1_TEXT_PAL_INDEX] =
      gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16 + DEBUG_BG1_TEXT_PAL_INDEX];
  LoadPalettes();

  for (i = 0; i < DEBUG_CHARS; i++)
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] =
        (gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] & 0x0FFF) | palMask;
}

void DebugMenuFormatListRow(u8 *out, const u8 *title, bool8 selected) {
  u8 i, t = 0;
  (void)selected;
  for (i = 0; i < DEBUG_CHARS; i++)
    out[i] = title[t] ? title[t++] : ' ';
  out[DEBUG_CHARS] = '\0';
}

void DebugMenuFormatTitleRow(u8 *out, const u8 *title) {
  u8 i, t = 0;

  for (i = 0; i < DEBUG_CHARS; i++)
    out[i] = title[t] ? title[t++] : ' ';
  out[DEBUG_CHARS] = '\0';
}

/* ------------------------------------------------------------------ */
/*  Text rows setup — clear to blank tile before drawing              */
/* ------------------------------------------------------------------ */

static void DebugMenuSetupTextRows(void) {
  u8 row, col;
  u16 palMask = DEBUG_BG1_TEXT_PAL_BANK << 12;

  /* ponytail: clear two extra rows above for section title (row 1) and spacing. */
  for (row = 0; row < DEBUG_ROWS + 2; row++)
    for (col = 0; col < DEBUG_CHARS; col++)
      gBgVram.sbb19[DEBUG_BG1_TEXT_ROW - 2 + row][DEBUG_SIDEBAR_COL_START + col] = palMask | 0;
}

/* ------------------------------------------------------------------ */
/*  Upload helpers                                                    */
/* ------------------------------------------------------------------ */

static void DebugMenuUploadText(void) {
  /* Upload glyph tiles (cbb1, tiles 200+, including the title row at row 2). */
  CpuCopy32(gBgVram.cbb1 + DEBUG_BG1_TEXT_TILE_BASE * 32,
            (void *)0x06004000 + DEBUG_BG1_TEXT_TILE_BASE * 32,
            (DEBUG_ROWS + 1) * DEBUG_CHARS * 32);
  CpuCopy32(gBgVram.sbb19, (void *)0x06009800, 0x800);
}

/* ponytail: cursor at tile 0 (cbb4+0x0 = 0x6010000, grid row 0). */
static void DebugMenuUploadObjTiles(void) {
  CpuCopy32(gBgVram.cbb4, DEBUG_OBJ_SAVE_ADDR, DEBUG_OBJ_SAVE_SIZE);
}

/* ------------------------------------------------------------------ */
/*  Redraw                                                            */
/* ------------------------------------------------------------------ */

static void DebugMenuClearAuxOam(void);
static void DebugMenuDrawSectionTitle(u8 view);

void DebugMenuRedraw(u16 scrollTop, u16 marker, u8 view) {
  DebugMenuSetupTextRows();
  if (view != DEBUG_VIEW_ROOT)
    DebugMenuDrawSectionTitle(view);
  switch (view) {
  case DEBUG_VIEW_MUSIC:
    DebugMenuDrawMusic(scrollTop, marker);
    break;
  case DEBUG_VIEW_PORTRAIT:
    DebugMenuDrawPortraits(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_SPRITE:
    DebugMenuDrawSprites(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_REACTION:
    DebugMenuDrawReactions(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_GRAPHIC:
    DebugMenuDrawGraphics(scrollTop, marker);
    break;
  case DEBUG_VIEW_VOICE:
    DebugMenuDrawVoices(scrollTop, marker);
    break;
  case DEBUG_VIEW_MATCH_SETTER:
    DebugMenuDrawMatchSetters(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_AI_MODE:
    DebugMenuDrawAiMode(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_RULESET:
    DebugMenuDrawRuleset(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_MAP:
    DebugMenuDrawMaps(scrollTop, (u8)marker);
    break;
  case DEBUG_VIEW_SCENE:
    DebugMenuDrawScenes(scrollTop, marker);
    break;
  case DEBUG_VIEW_DECK_PRESET:
    DebugMenuDrawDecks(scrollTop, (u8)marker);
    break;
  default:
    DebugMenuDrawRoot(scrollTop, (u8)marker);
    break;
  }
  /* ponytail: restore cursor palette in buffer so LoadPalettes writes the
   * correct value to palette RAM (sub-viewers may have clobbered bank 15). */
  CpuCopy16(gStartMenuCursorPalette,
            gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16, 32);
  DebugMenuUploadText();
  DebugMenuUploadObjTiles();
  LoadPalettes();
}

/* ------------------------------------------------------------------ */
/*  Graphics load                                                     */
/* ------------------------------------------------------------------ */

void DebugMenuLoadGraphics(void) {
  DebugMenuLoadCursorObjTiles();

  /* BG1 = solid black: blank tile 0 in cbb0, clear screenblock 0 entries. */
  CpuFill16(0, gBgVram.cbb0, 32);
  CpuFill16(0, gBgVram.cbb0, 0x800);

  /* Blank cbb1 tile 0 — BG0 uses it for the "empty" text background. */
  CpuFill16(0, gBgVram.cbb1, 32);
  DebugMenuSetupTextPalettes();

  /* Fill sbb19 (BG0 text tilemap) with palette bank 0. */
  CpuFill16(DEBUG_BG1_TEXT_PAL_BANK << 12, gBgVram.sbb19, sizeof(gBgVram.sbb19));

  /* Config: BG0 for text, BG1 = black, OBJ for cursor. */
  REG_DISPCNT = DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON;
  if (REG_DISPCNT & DISPCNT_BG2_ON)
    REG_DISPCNT |= DISPCNT_BG2_ON;
  if (REG_DISPCNT & DISPCNT_BG3_ON)
    REG_DISPCNT |= DISPCNT_BG3_ON;
  REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_16COLOR | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(DEBUG_BG0_SBB);
  REG_BG0HOFS = 0xFFF8; REG_BG0VOFS = 0;
  REG_BG1CNT = BGCNT_PRIORITY(2) | BGCNT_16COLOR | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(0);
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;

  CpuCopy32(gBgVram.cbb1, (void *)0x06004000, 0x4000);
  CpuCopy32(gBgVram.sbb19, (void *)0x06009800, 0x800);
  CpuCopy32(gBgVram.cbb0, (void *)0x06000000, 0x800);
  LoadPalettes();
  SetVBlankCallback(DebugMenuVBlank);
  DebugMenuUploadObjTiles();
  /* ponytail: init cursor OAM before first LoadOam so stale overworld
   * OAM doesn't show cursor tile 0 at (0,0). */
  DebugMenuClearAuxOam();
  DebugMenuUpdateCursor(0);
  LoadOam();
  DebugMenuVBlank();
  DebugMenuWaitVBlank();
}

/* ------------------------------------------------------------------ */
/*  Draw root                                                         */
/* ------------------------------------------------------------------ */

void DebugMenuDrawRoot(u8 scrollTop, u8 cursor) {
  u8 row, i;
  u16 palMask = DEBUG_BG1_TEXT_PAL_BANK << 12;
  (void)cursor;

  /* Clear the section-title row (row 1, DEBUG_BG1_TEXT_ROW - 2) across
   * full screen width — DebugMenuSetupTextRows only clears sidebar cols. */
  for (i = 0; i < 32; i++)
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW - 2][i] = palMask | 0;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;
    if (index < DEBUG_ROOT_ITEMS)
      DebugMenuCopyLine(row, sRootLabels[index]);
    else
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
  }
}

/* ------------------------------------------------------------------ */
/*  Highlight — yellow text replaces OBJ cursor                       */
/* ------------------------------------------------------------------ */

void DebugMenuHighlightRow(u8 row) {
  u8 i;
  u16 palMask = DEBUG_MENU_HIGHLIGHT_PAL_BANK << 12;
  u16 *vram = (u16 *)0x06009800 + (DEBUG_BG1_TEXT_ROW + row) * 32 + DEBUG_SIDEBAR_COL_START;

  /* Write directly to VRAM sbb19 — DebugMenuRedraw's upload already ran. */
  for (i = 0; i < DEBUG_CHARS; i++)
    vram[i] = (vram[i] & 0x0FFF) | palMask;
}

/* ------------------------------------------------------------------ */
/*  Cursor / input helpers                                            */
/* ------------------------------------------------------------------ */

void DebugMenuUpdateCursorSlot(u8 oamSlot, u8 screenRow, u8 paletteNum) {
  u32 *oam = (u32 *)&gOamBuffer[oamSlot * 4];

  oam[0] = ((screenRow << 3) + (DEBUG_CURSOR_Y_TILES * 8) - 4) |
           ((u32)(DEBUG_CURSOR_X | (DEBUG_CURSOR_SIZE << 14)) << 16);
  oam[1] = 0 | ((paletteNum & 0xF) << 12);  /* tile 0 at cbb4+0x0 = 0x6010000 */
}

void DebugMenuUpdateCursor(u8 screenRow) {
  DebugMenuUpdateCursorSlot(0, screenRow, DEBUG_MENU_CURSOR_PAL_SLOT);
  DebugMenuHighlightRow(screenRow);
}

void DebugMenuLatchButtons(void) {
  gPressedButtons = ~REG_KEYINPUT;
  gNewButtons = 0;
  gRepeatedOrNewButtons = 0;
  gRepeatedButtonsCounter = 10;
}

void DebugMenuWaitRelease(u16 mask) {
  SetVBlankCallback(DebugMenuVBlank);
  while (gPressedButtons & mask)
    DebugMenuWaitVBlank();
  DebugMenuLatchButtons();
  gInputRepeatTimer = 0;
}

u16 DebugMenuButtons(void) {
  return gNewButtons | (gRepeatedOrNewButtons & (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT));
}

/* ------------------------------------------------------------------ */
/*  OAM helpers — must precede DebugMenuRoot                           */
/* ------------------------------------------------------------------ */

static void DebugMenuClearCursorOam(void) {
  u32 *oam = (u32 *)&gOamBuffer[0 * 4];
  oam[0] = 160;
  oam[1] = 0;
}

/* Sub-viewers (portrait/sprite/reaction) leave OAM slots 1+ dirty.
 * Clear them before the root menu renders so no ghost sprites bleed in. */
static void DebugMenuClearAuxOam(void) {
  CpuFill16(0, gOamBuffer + 4, 0x3F8);
}

/* ------------------------------------------------------------------ */
/*  Section title — centered X at col 7, SBB row 1 (8 px down)       */
/* ------------------------------------------------------------------ */

/* Screen = 30 tiles wide.  16 chars × 8 px = 128 px.  Center: (30-16)/2 = 7 tiles. */
#define DEBUG_SECTION_TITLE_COL 7

static const u8 *const sSectionTitles[] APPEND_RODATA = {
    [DEBUG_VIEW_MUSIC]         = sText_SectionMusic,
    [DEBUG_VIEW_PORTRAIT]      = sText_SectionPortrait,
    [DEBUG_VIEW_SPRITE]        = sText_SectionSprite,
    [DEBUG_VIEW_REACTION]      = sText_SectionReaction,
    [DEBUG_VIEW_GRAPHIC]       = sText_SectionGraphic,
    [DEBUG_VIEW_VOICE]         = sText_SectionVoice,
    [DEBUG_VIEW_MATCH_SETTER]  = sText_SectionMatch,
    [DEBUG_VIEW_AI_MODE]       = sText_SectionAiMode,
    [DEBUG_VIEW_RULESET]       = sText_SectionRuleset,
    [DEBUG_VIEW_MAP]           = sText_SectionMap,
    [DEBUG_VIEW_SCENE]         = sText_SectionScene,
    [DEBUG_VIEW_DECK_PRESET]   = sText_SectionDecks,
};

static void DebugMenuDrawSectionTitle(u8 view) {
  const u8 *title;
  u8 i, j;
  u16 palMask = DEBUG_BG1_TEXT_PAL_BANK << 12;
  /* ponytail: title tiles past the list range (row 440-455, after 15×16 list tiles). */
  u16 tileBase = DEBUG_BG1_TEXT_TILE_BASE + DEBUG_ROWS * DEBUG_CHARS;

  if (view >= ARRAY_COUNT(sSectionTitles) || sSectionTitles[view] == NULL)
    return;
  title = sSectionTitles[view];

  /* Render title at tileBase in cbb1, shift pixels, write SBB row 2. */
  CopyStringTilesToVRAMBuffer((u8 *)gBgVram.cbb1 + tileBase * 32, title, 0x001);
  for (j = 0; j < DEBUG_CHARS; j++) {
    u8 *tile = (u8 *)gBgVram.cbb1 + (tileBase + j) * 32;
    for (i = 0; i < 32; i++) {
      u8 p = tile[i];
      u8 lo = p & 0xF;
      u8 hi = p >> 4;
      if (lo == 1) lo = DEBUG_BG1_TEXT_PAL_INDEX;
      if (hi == 1) hi = DEBUG_BG1_TEXT_PAL_INDEX;
      tile[i] = lo | (hi << 4);
    }
  }
  for (i = 0; i < DEBUG_CHARS; i++)
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW - 2][DEBUG_SECTION_TITLE_COL + i] =
        palMask | (tileBase + i);
}

/* ------------------------------------------------------------------ */
/*  Root menu loop                                                    */
/* ------------------------------------------------------------------ */

static void DebugMenuRoot(void) {
  u8 cursor = 0, scrollTop = 0;
  DebugMenuLatchButtons();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  DebugMenuClearAuxOam();
  while (1) {
    u16 buttons = DebugMenuButtons();
    if (buttons & R_BUTTON)
      REG_DISPCNT ^= DISPCNT_BG0_ON;
    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop) scrollTop = cursor;
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
    }
    if (buttons & DPAD_DOWN && cursor < DEBUG_ROOT_ITEMS - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      DebugMenuWaitRelease(A_BUTTON);
      DebugMenuLatchButtons();
      if (cursor == 0) DebugMusicViewer();
      else if (cursor == 1) DebugPortraitViewer();
      else if (cursor == 2) DebugSpriteViewer();
      else if (cursor == 3) DebugReactionViewer();
      else if (cursor == 4) DebugGraphicViewer();
      else if (cursor == 5) DebugVoiceViewer();
      else if (cursor == 6) DebugMatchSetterViewer();
      else if (cursor == 7) DebugMapViewer();
      else if (cursor == 8) DebugSceneViewer();
      else if (cursor == 9) DebugAiModeViewer();
      else if (cursor == 10) DebugRulesetViewer();
      else if (cursor == 11) DebugDeckPresetViewer();
      else { gDebugMenuPendingSaveAnywhere = TRUE; break; }
      DebugMenuLatchButtons();
      scrollTop = 0;
      if (cursor >= DEBUG_ROWS) scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
      DebugMenuClearAuxOam();
    }
    DebugMenuUpdateCursor(cursor - scrollTop);
    LoadOam();
    DebugMenuWaitVBlank();
  }
}

/* ------------------------------------------------------------------ */
/*  Entry / exit                                                      */
/* ------------------------------------------------------------------ */

extern u8 gDebugMenuMapViewerInitialLocation;
extern u8 gDebugMenuPendingSceneActive;

void DebugMenuMain(void) {
  /* Save overworld display state so we can fully restore it on exit. */
  const u16 savedDispcnt = REG_DISPCNT;
  const u16 savedBldCnt = REG_BLDCNT;
  const u16 savedBldAlpha = REG_BLDALPHA;
  const u16 savedBldY = REG_BLDY;
  const u16 savedWinIn = REG_WININ;
  const u16 savedWinOut = REG_WINOUT;
  const u16 savedBg0Cnt = REG_BG0CNT;
  /* ponytail: dont save WINxH/WINxV — they change per-scene and the
   * overworld dialogue resets them via sub_80533BC. */

  InitButtonMaps();
  MatchSetter_Init();
  gDebugMenuMapViewerInitialLocation = 0xFF;
  gDebugMenuPendingSceneActive = 0xFF;
  gDebugMenuPendingSaveAnywhere = FALSE;
  DebugMenuLoadGraphics();
  DebugMenuLatchButtons();
  DebugMenuRoot();
  DebugMenuWaitRelease(B_BUTTON);
  DebugMenuClearPortraitObjStash();
  DebugMenuClearSpriteObjStash();
  DebugMenuClearCursorOam();

  /* Clear EVERY OAM slot that might have stale debug-menu data. */
  {
    u8 i;
    for (i = 0; i < 128; i++) {
      u32 *oam = (u32 *)&gOamBuffer[i * 4];
      oam[0] = 160; /* Y=160 hides the sprite */
      oam[1] = 0;
    }
  }
  LoadOam();

  /* Restore overworld OBJ tiles that the cursor overwrote. */
  CpuFastCopy(DEBUG_OBJ_SAVE_BUF, gBgVram.cbb4, DEBUG_OBJ_SAVE_SIZE);
  CpuFastCopy(DEBUG_OBJ_SAVE_BUF, DEBUG_OBJ_SAVE_ADDR, DEBUG_OBJ_SAVE_SIZE);

  /* Restore overworld font palette (bank 0) that the debug menu wrote to. */
  CallThumbVoid(0x0804F598);
  LoadPalettes();

  /* Fully restore overworld display registers. */
  REG_BG0CNT = savedBg0Cnt;
  REG_BLDCNT = savedBldCnt;
  REG_BLDALPHA = savedBldAlpha;
  REG_BLDY = savedBldY;
  REG_WININ = savedWinIn;
  REG_WINOUT = savedWinOut;
  REG_DISPCNT = savedDispcnt & ~DISPCNT_BG0_ON;
  SetVBlankCallback((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1));
}

void DebugMenuLoadReactionObjPalettes(void) {
  CpuCopy16(gOverworldEntityPalettes, gPaletteBuffer + 256, 0x180);
  CpuCopy16(gStartMenuCursorPalette,
            gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16, 32);
  LoadPalettes();
}
