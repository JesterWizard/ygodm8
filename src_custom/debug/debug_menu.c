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
extern u8 gStartMenuCursorTiles[];
extern u16 gStartMenuCursorPalette[];

static const u8 sDebugMenuBg[] APPEND_ASSET = INCBIN_U8("src_custom/assets/menus/debug_menu.lz");
static const u16 sDebugMenuBgPal[] APPEND_ASSET = INCBIN_U16("src_custom/assets/menus/debug_menu.gbapal");

static const u8 sText_RootMusic[] APPEND_RODATA = "Music      ";
static const u8 sText_RootPortrait[] APPEND_RODATA = "Portrait   ";
static const u8 sText_RootSprite[] APPEND_RODATA = "Sprite     ";
static const u8 sText_RootReaction[] APPEND_RODATA = "Reaction   ";
static const u8 sText_RootGraphic[] APPEND_RODATA = "Graphic    ";
static const u8 sText_RootVoice[] APPEND_RODATA = "Voice      ";
static const u8 sText_RootMatchSetter[] APPEND_RODATA = "Match Set  ";
static const u8 sText_RootMap[] APPEND_RODATA = "Map Tel    ";
static const u8 sText_RootScene[] APPEND_RODATA = "Scene      ";
static const u8 sText_RootAiMode[] APPEND_RODATA = "AI Mode    ";
static const u8 sText_RootRuleset[] APPEND_RODATA = "Ruleset    ";
static const u8 sText_RootDeckPreset[] APPEND_RODATA = "Decks      ";
static const u8 sText_RootSaveAnywhere[] APPEND_RODATA = "Save Anywhr";
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
void LoadObjVRAM(void);
void LoadPalettes(void);
void LoadBgOffsets(void);
void LoadOam(void);
void SetVBlankCallback(void (*)(void));

/* ------------------------------------------------------------------ */
/*  VBlank — keep the overworld rendering via sub_804F1E4              */
/*  ponytail: preserve upper bytes of WININ/WINOUT (WIN1 / OBJWIN)    */
/*  so we don't break the overworld textbox window.                   */
/* ------------------------------------------------------------------ */

static void DebugMenuVBlank(void) {
  /* Let overworld VBlank run first — it re-enables BG0 + sets scroll. */
  ((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1))();
  /* Then clobber every register the overworld just touched. */
  REG_DISPCNT = DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON;
  REG_BG0CNT = BGCNT_PRIORITY(1) | BGCNT_16COLOR | BGCNT_CHARBASE(DEBUG_BG1_CBB) | BGCNT_SCREENBASE(DEBUG_BG0_SBB);
  REG_BG0HOFS = 0;  REG_BG0VOFS = 0;
  REG_BG1CNT = BGCNT_PRIORITY(0) | BGCNT_16COLOR | BGCNT_CHARBASE(DEBUG_BG1_CBB) | BGCNT_SCREENBASE(DEBUG_BG1_SBB);
  REG_BG1HOFS = 0;  REG_BG1VOFS = 0;
  REG_BLDCNT = 0;   /* no blending */
  REG_BLDALPHA = 0;
}

void DebugMenuVBlankNoWin(void) {
  ((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1))();
}

void DebugMenuWaitVBlank(void) {
  SetVBlankCallback(DebugMenuVBlank);
  WaitForVBlank();
}

/* ------------------------------------------------------------------ */
/*  BG1 sidebar tilemap setup (columns 0-9)                           */
/* ------------------------------------------------------------------ */

static void DebugMenuSetupSidebarTilemap(void) {
  u8 i, j;

  for (i = 0; i < 20; i++) {
    for (j = 0; j < DEBUG_SIDEBAR_COLS; j++) {
      gBgVram.sbb18[i][DEBUG_SIDEBAR_COL_START + j] =
          (i * DEBUG_SIDEBAR_COLS + j + 1) | (DEBUG_SIDEBAR_PAL_BANK << 12);
    }
  }
}

/* ------------------------------------------------------------------ */
/*  BG1 text rendering — small overworld font in cbb1 (tiles 200+)    */
/* ------------------------------------------------------------------ */

void DebugMenuCopyLine(u8 row, const u8 *text) {
  u8 i;
  u8 *glyphDest = (u8 *)gBgVram.cbb1 + (DEBUG_BG1_TEXT_TILE_BASE + row * DEBUG_CHARS) * 32;
  u16 tileBase = DEBUG_BG1_TEXT_TILE_BASE + row * DEBUG_CHARS;
  u16 palMask = DEBUG_BG1_TEXT_PAL_BANK << 12;

  /* Render small font glyphs into cbb1 after sidebar art. */
  CopyStringTilesToVRAMBuffer(glyphDest, text, 0x001);

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
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16], 32);
}

void DebugMenuSetLinePalette(u8 row, u8 paletteNum) {
  u8 i;
  u16 palMask = (paletteNum & 0xF) << 12;

  for (i = 0; i < DEBUG_CHARS; i++)
    gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] =
        (gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + i] & 0x0FFF) | palMask;
}

void DebugMenuFormatListRow(u8 *out, const u8 *title, bool8 selected) {
  u8 i, t = 0;

  out[0] = selected ? '>' : ' ';
  for (i = 1; i < DEBUG_CHARS; i++)
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

  for (row = 0; row < DEBUG_ROWS; row++) {
    for (col = 0; col < DEBUG_CHARS; col++)
      gBgVram.sbb19[DEBUG_BG1_TEXT_ROW + row][DEBUG_SIDEBAR_COL_START + col] = palMask | 0;
  }
}

/* ------------------------------------------------------------------ */
/*  Upload helpers                                                    */
/* ------------------------------------------------------------------ */

/* Upload BG1 charblock + tilemaps to real VRAM.
   ponytail: cbb1 upload covers both sidebar art and text glyphs.
   sbb18 = BG1 tilemap -> VRAM 0x06009000 (SB 18).
   sbb19 = BG0 tilemap -> VRAM 0x06009800 (SB 19).
   Screen blocks are 0x800 bytes each: SB n = 0x06000000 + n*0x800. */
static void DebugMenuUploadBg1(void) {
  CpuCopy32(gBgVram.cbb1, (void *)0x06004000, 0x4000);
  CpuCopy32(gBgVram.sbb18, (void *)0x06009000, 0x800);
  CpuCopy32(gBgVram.sbb19, (void *)0x06009800, 0x800);
}

/* ------------------------------------------------------------------ */
/*  Redraw                                                            */
/* ------------------------------------------------------------------ */

void DebugMenuRedraw(u16 scrollTop, u16 marker, u8 view) {
  DebugMenuSetupTextRows();
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
  DebugMenuUploadBg1();
  LoadPalettes();
}

/* ------------------------------------------------------------------ */
/*  Graphics load                                                     */
/* ------------------------------------------------------------------ */

void DebugMenuLoadGraphics(void) {
  s16 i;
  u8 r, c;

  /* Decompress sidebar art into cbb1 buffer, shift tile 0 blank,
   * then upload to VRAM via CpuCopy32. */
  LZ77UnCompWram(sDebugMenuBg, gBgVram.cbb1);
  for (i = DEBUG_SIDEBAR_TILES - 1; i >= 0; i--)
    CpuCopy32(gBgVram.cbb1 + i * 32, gBgVram.cbb1 + (i + 1) * 32, 32);
  CpuFill16(0, gBgVram.cbb1, 32);

  /* Decompress cursor tiles into cbb4. */
  LZ77UnCompWram(gStartMenuCursorTiles, gBgVram.cbb4);

  /* Sidebar palette -> buffer bank 14 -> LoadPalettes pushes to HW. */
  CpuCopy16(sDebugMenuBgPal, gPaletteBuffer + DEBUG_SIDEBAR_PAL_BANK * 16, 32);

  /* Text palette into bank 15. Force entry 0 transparent. */
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16], 32);
  gPaletteBuffer[DEBUG_BG1_TEXT_PAL_BANK * 16] = 0;  /* color 0 = transparent */

  /* Cursor palette into OBJ slot 0. */
  CpuCopy16(gStartMenuCursorPalette, gPaletteBuffer + 256, 32);

  /* Fill sbb19 (BG0 tilemap) — all entries use palette bank 15 so color 0
   * is explicitly transparent, not black from overworld palette bank 0. */
  CpuFill16(DEBUG_BG1_TEXT_PAL_BANK << 12, gBgVram.sbb19, sizeof(gBgVram.sbb19));

  /* Fill sbb18 tilemap with correct tile indices. */
  CpuFill16(0, gBgVram.sbb18, sizeof(gBgVram.sbb18));
  for (r = 0; r < 20; r++)
    for (c = 0; c < DEBUG_SIDEBAR_COLS; c++)
      gBgVram.sbb18[r][DEBUG_SIDEBAR_COL_START + c] =
          (r * DEBUG_SIDEBAR_COLS + c + 1) | (DEBUG_SIDEBAR_PAL_BANK << 12);

  /* Config registers: BG0 (sbb19 = text overlay, priority 1 behind art),
   * BG1 (sbb18 = sidebar art, priority 0 front). No windows, no blending. */
  REG_DISPCNT = DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON;
  REG_BG0CNT = BGCNT_PRIORITY(1) | BGCNT_16COLOR | BGCNT_CHARBASE(DEBUG_BG1_CBB) | BGCNT_SCREENBASE(DEBUG_BG0_SBB);
  REG_BG1CNT = BGCNT_PRIORITY(0) | BGCNT_16COLOR | BGCNT_CHARBASE(DEBUG_BG1_CBB) | BGCNT_SCREENBASE(DEBUG_BG1_SBB);
  REG_BG0HOFS = 0; REG_BG0VOFS = 0;
  REG_BG1HOFS = 0; REG_BG1VOFS = 0;
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;

  /* Upload buffers to real VRAM, push palette to HW. */
  CpuCopy32(gBgVram.cbb1, (void *)0x06004000, 0x4000);
  CpuCopy32(gBgVram.sbb18, (void *)0x06009000, 0x800);
  CpuCopy32(gBgVram.sbb19, (void *)0x06009800, 0x800);
  LoadPalettes();

  SetVBlankCallback(DebugMenuVBlank);
  LoadObjVRAM();
  DebugMenuVBlank();
  DebugMenuWaitVBlank();
}

/* ------------------------------------------------------------------ */
/*  Draw root                                                         */
/* ------------------------------------------------------------------ */

void DebugMenuDrawRoot(u8 scrollTop, u8 cursor) {
  u8 row;

  (void)cursor;

  for (row = 0; row < DEBUG_ROWS; row++) {
    u8 index = scrollTop + row;

    if (index < DEBUG_ROOT_ITEMS)
      DebugMenuCopyLine(row, sRootLabels[index]);
    else
      DebugMenuCopyLine(row, gDebugMenuBlankLine);
  }
}

/* ------------------------------------------------------------------ */
/*  Cursor / input helpers                                            */
/* ------------------------------------------------------------------ */

void DebugMenuUpdateCursorSlot(u8 oamSlot, u8 screenRow, u8 paletteNum) {
  u32 *oam = (u32 *)&gOamBuffer[oamSlot * 4];

  oam[0] = (screenRow << 3) + (DEBUG_CURSOR_Y_TILES * 8) |
           ((u32)DEBUG_CURSOR_X << 16);
  oam[1] = 0x800 | ((paletteNum & 0xF) << 12);
}

void DebugMenuUpdateCursor(u8 screenRow) {
  DebugMenuUpdateCursorSlot(0, screenRow, 0);
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
/*  Root menu loop                                                    */
/* ------------------------------------------------------------------ */

static void DebugMenuRoot(void) {
  u8 cursor = 0, scrollTop = 0;

  DebugMenuLatchButtons();
  DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & R_BUTTON)
      REG_DISPCNT ^= DISPCNT_BG0_ON;
    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
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
      if (cursor == 0)
        DebugMusicViewer();
      else if (cursor == 1)
        DebugPortraitViewer();
      else if (cursor == 2)
        DebugSpriteViewer();
      else if (cursor == 3)
        DebugReactionViewer();
      else if (cursor == 4)
        DebugGraphicViewer();
      else if (cursor == 5)
        DebugVoiceViewer();
      else if (cursor == 6)
        DebugMatchSetterViewer();
      else if (cursor == 7)
        DebugMapViewer();
      else if (cursor == 8)
        DebugSceneViewer();
      else if (cursor == 9)
        DebugAiModeViewer();
      else if (cursor == 10)
        DebugRulesetViewer();
      else if (cursor == 11)
        DebugDeckPresetViewer();
      else {
        gDebugMenuPendingSaveAnywhere = TRUE;
        break;
      }
      DebugMenuLatchButtons();
      scrollTop = 0;
      if (cursor >= DEBUG_ROWS)
        scrollTop = cursor - (DEBUG_ROWS - 1);
      DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_ROOT);
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
  /* Restore overworld VBlank + disable debug menu BG layers + windows. */
  REG_DISPCNT &= ~(DISPCNT_BG1_ON | DISPCNT_BG0_ON);
  SetVBlankCallback((void (*)(void))(THUMB_VBLANK_OVERWORLD | 1));
}

void DebugMenuLoadReactionObjPalettes(void) {
  CpuCopy16(gOverworldEntityPalettes, gPaletteBuffer + 256, 0x180);
  CpuCopy16(gStartMenuCursorPalette,
            gPaletteBuffer + 256 + DEBUG_MENU_CURSOR_PAL_SLOT * 16, 32);
  LoadPalettes();
}
