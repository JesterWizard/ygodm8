#include "global.h"
#include "configs/runtime.h"
#include "menu_cursor.h"

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

/* 16x16 gbagfx tiles are linear (TL,TR,BL,BR). Start-menu OBJ uses 2D mapping. */
#define MENU_CURSOR_TILE_BYTES 32
#define MENU_CURSOR_TILE_STRIDE 32

static const u8 sCursorEyeTiles[] APPEND_ASSET =
    INCBIN_U8("src_custom/assets/cursors/cursor_eye.4bpp");
static const u16 sCursorEyePal[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cursors/cursor_eye.gbapal");

static const u8 sCursorKuribohTiles[] APPEND_ASSET =
    INCBIN_U8("src_custom/assets/cursors/cursor_kuriboh.4bpp");
static const u16 sCursorKuribohPal[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cursors/cursor_kuriboh.gbapal");

static const u8 sCursorPuzzleTiles[] APPEND_ASSET =
    INCBIN_U8("src_custom/assets/cursors/cursor_puzzle.4bpp");
static const u16 sCursorPuzzlePal[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cursors/cursor_puzzle.gbapal");

static const u8 *const sCursorTiles[MENU_CURSOR_COUNT] APPEND_RODATA = {
    sCursorEyeTiles,
    sCursorKuribohTiles,
    sCursorPuzzleTiles,
};

static const u16 *const sCursorPals[MENU_CURSOR_COUNT] APPEND_RODATA = {
    sCursorEyePal,
    sCursorKuribohPal,
    sCursorPuzzlePal,
};

static void MenuCursor_Normalize(void) {
  if (gMenuCursorId >= MENU_CURSOR_COUNT)
    gMenuCursorId = MENU_CURSOR_EYE;
}

u8 MenuCursor_GetId(void) {
  MenuCursor_Normalize();
  return gMenuCursorId;
}

void MenuCursor_SetId(u8 id) {
  gMenuCursorId = id < MENU_CURSOR_COUNT ? id : MENU_CURSOR_EYE;
  MenuCursor_SaveToFlashPrimary();
  MenuCursor_SaveToFlashBackup();
}

void MenuCursor_LoadTiles(void *dest) {
  const u8 *src;
  u8 *dst = dest;

  MenuCursor_Normalize();
  src = sCursorTiles[gMenuCursorId];
  /* Clear span covering tiles 0..33 so leftover LZ garbage cannot show. */
  CpuFill16(0, dst, (MENU_CURSOR_TILE_STRIDE + 2) * MENU_CURSOR_TILE_BYTES);
  CpuCopy32(src + 0 * MENU_CURSOR_TILE_BYTES, dst + 0 * MENU_CURSOR_TILE_BYTES,
            MENU_CURSOR_TILE_BYTES);
  CpuCopy32(src + 1 * MENU_CURSOR_TILE_BYTES, dst + 1 * MENU_CURSOR_TILE_BYTES,
            MENU_CURSOR_TILE_BYTES);
  CpuCopy32(src + 2 * MENU_CURSOR_TILE_BYTES,
            dst + MENU_CURSOR_TILE_STRIDE * MENU_CURSOR_TILE_BYTES,
            MENU_CURSOR_TILE_BYTES);
  CpuCopy32(src + 3 * MENU_CURSOR_TILE_BYTES,
            dst + (MENU_CURSOR_TILE_STRIDE + 1) * MENU_CURSOR_TILE_BYTES,
            MENU_CURSOR_TILE_BYTES);
}

void MenuCursor_LoadPalette(u16 *dest) {
  MenuCursor_Normalize();
  CpuCopy16(sCursorPals[gMenuCursorId], dest, 32);
}

u16 MenuCursor_GetColor(u8 index) {
  MenuCursor_Normalize();
  if (index >= 16)
    return 0;
  return sCursorPals[gMenuCursorId][index];
}

static void MenuCursor_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, &gMenuCursorId, 1);
  MenuCursor_Normalize();
}

void MenuCursor_LoadFromFlashPrimary(void) {
  MenuCursor_LoadFromFlash((int)&gMenuCursorIdFlashPrimary);
}

void MenuCursor_LoadFromFlashBackup(void) {
  MenuCursor_LoadFromFlash((int)&gMenuCursorIdFlashBackup);
}

void MenuCursor_SaveToFlashPrimary(void) {
  sub_80588C4(&gMenuCursorId, (int)&gMenuCursorIdFlashPrimary, 1);
}

void MenuCursor_SaveToFlashBackup(void) {
  sub_80588C4(&gMenuCursorId, (int)&gMenuCursorIdFlashBackup, 1);
}

void MenuCursor_Reset(void) {
  gMenuCursorId = MENU_CURSOR_EYE;
}
