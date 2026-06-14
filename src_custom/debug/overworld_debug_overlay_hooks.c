#include "global.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "debug_menu.h"
#include "gba/io_reg.h"
#include "gfx_reg_buffers.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"
#include "text.h"

void sub_804F1E4(void);
void sub_804EC4C(void);
void sub_804ECA8(void);
void sub_804EC64(void);
void sub_804EEE0(void);
void sub_804F218(void);
void sub_8053E34(u8);
void LoadBgOffsets(void);
void LoadOam(void);
void sub_80551B8(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void OverworldSetRegDispcnt(void);
void sub_8045284(u16 *, u16, u16);

extern const u32 g82AD2D0[];
extern u16 g82AD48C[];

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

// Overworld BG0 textbox/font: gVramBuffer + 0xD800 (tiles), + 0xE800 (= gBgVram.sbb1D tilemap).
#define OVERWORLD_BG0_CHARBUF_OFFSET 0xE680
#define OVERWORLD_BG0_TILEMAP_OFFSET 0xE800

#define OVERLAY_BASE_TILE_ID 0x134
#define OVERLAY_MAX_CHARS 12
#define OVERLAY_CHARBUF_SIZE (OVERLAY_MAX_CHARS * 32)

#define OVERLAY_ROW 1
#define OVERLAY_COL 2

static int ClampInt(int value, int min, int max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

static void UploadOverworldBg0Base(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  CpuCopy16(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET, (void *)0x0600E800, 0x500);
}

static void ClearOverlayTilemap(void) {
  u16 *tilemap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  u16 attrs = tilemap[OVERLAY_ROW * 32 + OVERLAY_COL] & 0xFC00;
  int i;

  for (i = 0; i < OVERLAY_MAX_CHARS; i++)
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | 0xC0);
}

static char *AppendSignedInt(char *out, int value) {
  char tmp[12];
  unsigned u;
  int n = 0;
  int i;

  if (value < 0) {
    *out++ = '-';
    u = (unsigned)(-value);
  } else {
    u = (unsigned)value;
  }

  do {
    tmp[n++] = (char)('0' + (u % 10));
    u /= 10;
  } while (u && n < (int)sizeof(tmp));

  for (i = n - 1; i >= 0; i--)
    *out++ = tmp[i];

  return out;
}

static void WriteOverlayString(const char *str) {
  u16 *tilemap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  u16 attrs = tilemap[OVERLAY_ROW * 32 + OVERLAY_COL] & 0xFC00;
  int i;

  CopyStringTilesToVRAMBuffer(
      gVramBuffer + OVERWORLD_BG0_CHARBUF_OFFSET,
      (const u8 *)str,
      0x001);

  for (i = 0; i < OVERLAY_MAX_CHARS; i++) {
    if (str[i] == '\0')
      break;
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | (OVERLAY_BASE_TILE_ID + i));
  }
  for (; i < OVERLAY_MAX_CHARS; i++)
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | 0xC0);
}

static void OverworldOverlay_PatchVram(void) {
  vu16 *vramMap = (vu16 *)0x0600E800;
  u16 *bufMap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  int i;

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    CpuCopy16(gVramBuffer + OVERWORLD_BG0_CHARBUF_OFFSET, (void *)0x0600E680, OVERLAY_CHARBUF_SIZE);

  for (i = 0; i < OVERLAY_MAX_CHARS; i++)
    vramMap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = bufMap[OVERLAY_ROW * 32 + OVERLAY_COL + i];
}

static void OverworldOverlay_Update(void) {
  int screenX;
  int screenY;
  char buf[OVERLAY_MAX_CHARS + 1];
  char *p;

  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE) {
    ClearOverlayTilemap();
    return;
  }

  screenX = gOverworld.objects[0].x * 2 + gOverworld.unk24E - 16;
  screenY = gOverworld.objects[0].y * 2 + gOverworld.unk24C - 24 - gOverworld.objects[0].unk8 -
            gOverworld.objects[0].unkA;

  screenX = ClampInt(screenX, 0, 239);
  screenY = ClampInt(screenY, 0, 159);
  p = buf;

  *p++ = 'X';
  *p++ = ':';
  p = AppendSignedInt(p, screenX);
  *p++ = ' ';
  *p++ = 'Y';
  *p++ = ':';
  p = AppendSignedInt(p, screenY);
  *p = '\0';

  WriteOverlayString(buf);
}

void OverworldOverlay_PrepareFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Update();
}

void OverworldOverlay_CommitFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_PatchVram();
}

void OverworldOverlay_OnWalkFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  OverworldOverlay_PrepareFrame();
  OverworldOverlay_CommitFrame();
}

void OverworldOverlay_RestoreDisplayRegs(void) {
  REG_WINOUT = 0x3D3F;
  REG_BLDCNT = 0;
  REG_BLDY = 0;
}

void OverworldOverlay_Refresh(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  OverworldOverlay_Update();
  UploadOverworldBg0Base();
  OverworldOverlay_PatchVram();
  SetVBlankCallback(sub_804F1E4);
}

LYN_REPLACE_CHECK(OverworldLoadGraphics);
void OverworldLoadGraphics__Replacement(void) {
  REG_DISPCNT = 0;
  REG_BLDCNT = 0;
  CallThumbVoid(0x0804DCE8);
  CallThumbVoid(0x0804EDA0);
  CallThumbVoid(0x0804EDC8);
  CallThumbVoid(0x0804EDF0);
  CallThumbVoid(0x0804EE18);
  CallThumbVoid(0x0804EE6C);
  DebugMenuClearPortraitObjStash();
  if (CheckFlag(0xF3))
    sub_8044E50(gPaletteBuffer, 0x10, 0x1FF);
  if (CheckFlag(0xF0))
    sub_8044EC8(gPaletteBuffer, 0x10, 0x1FF, 6);
  if (CheckFlag(0xEF))
    sub_8045284(gPaletteBuffer, 0x10, 0xFF);
  REG_BLDY = 0;
  WaitForVBlank();
  sub_804EC4C();
  OverworldOverlay_RestoreDisplayRegs();
  OverworldSetRegDispcnt();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
}

LYN_REPLACE_CHECK(sub_8053E34);
void sub_8053E34__Replacement(u8 arg0) {
  int i, temp;

  CallThumbVoid(0x0805339C);
  OverworldSetRegDispcnt();
  REG_BLDCNT = 0xFF;
  REG_WINOUT = 0x3D3E;
  for (i = 0; i < 16; i++) {
    REG_BLDY = i;
    temp = arg0;
    while (--temp != -1)
      sub_804F218();
  }
  OverworldOverlay_RestoreDisplayRegs();
  OverworldSetRegDispcnt();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_OnWalkFrame();
}

/* LYN_REPLACEMENT(sub_80532A8) */
void sub_80532A8__Replacement(struct ScriptCtx *unused) {
  LZ77UnCompWram(g82AD2D0, gVramBuffer + 0xD800);
  CpuCopy16(g82AD48C, gVramBuffer + 0xE800, 0x500);
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
  SetVBlankCallback(sub_804ECA8);
  WaitForVBlank();
}

LYN_REPLACE_CHECK(sub_804EEE0);
void sub_804EEE0__Replacement(void) {
  OverworldOverlay_PrepareFrame();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x4000);
  OverworldOverlay_CommitFrame();
}

LYN_REPLACE_CHECK(sub_804F1E4);
void sub_804F1E4__Replacement(void) {
  LoadBgOffsets();
  LoadOam();
}

LYN_REPLACE_CHECK(sub_804ECA8);
void sub_804ECA8__Replacement(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  LoadOam();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE
      && gDebugSaveAnywherePendingCapture != TRUE)
    OverworldOverlay_PatchVram();
  else if (gDebugSaveAnywherePendingCapture != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
}

LYN_REPLACE_CHECK(sub_804F218);
void sub_804F218__Replacement(void) {
  OverworldOverlay_PrepareFrame();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  sub_80551B8();
  SetVBlankCallback(LoadBgOffsets);
  WaitForVBlank();
  LoadOam();
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE
      && gDebugSaveAnywherePendingCapture != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
  LoadObjVRAM();
  LoadPalettes();
  OverworldOverlay_CommitFrame();
}

LYN_REPLACE_CHECK(sub_804EC64);
void sub_804EC64__Replacement(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
  LoadObjVRAM();
  LoadPalettes();
  LoadOam();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
  SetVBlankCallback(sub_804F1E4);
}

LYN_REPLACE_CHECK(sub_804EC4C);
void sub_804EC4C__Replacement(void) {
  LoadBgOffsets();
  LoadOam();
  LoadVRAM();
  LoadPalettes();

  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  SetVBlankCallback(sub_804F1E4);

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
}
